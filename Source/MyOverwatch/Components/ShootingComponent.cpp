// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "ShootingComponent.h"
#include "./Components/RaycastShootingComponent.h"
#include "CharacterSkillCaster.h"
#include "./Characters/Projectile.h"


// Sets default values for this component's properties
UShootingComponent::UShootingComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootingComponent::BeginPlay(){
	Super::BeginPlay();
	CurrentAmmo = TotalAmmo;

	FirstPersonCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	SkillCaster = GetOwner()->FindComponentByClass<UCharacterSkillCaster>();
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPlayerShooting && FiringState == EFiringState::READY /*&& !bIsShiftCasted*/) { Shoot(); }

	if (FiringState == EFiringState::NOT_READY) { MakeReadyGunToNextShot(); }

	if (FiringState == EFiringState::OUT_OF_AMMO) { ReloadGun(); }

}

void UShootingComponent::Shoot() {

	FiringState = EFiringState::NOT_READY;


	//If no bullet change firing state to Out_Of_Ammo.
	if (CurrentAmmo <= 0) {
		FiringState = EFiringState::OUT_OF_AMMO;
		return;
	}
	CurrentAmmo--;

	PlayFiringSound();
	PlayFiringAnimation();

	//Choose firing type and fire.
	if (bEnableRayCastShooting) {
		for (int32 i = 0; i < TotalBulletPerShot; i++) {
			AActor* EnemyToDamage = nullptr;
			EnemyToDamage = RayShoot();
			DamageToEnemy(EnemyToDamage);
		}
	}
	else if (bEnableProjectileShooting) {
		if (FirstPersonCamera == NULL) { return; }
		SpawnProjectile();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Both is projectile shooting and raycast shooting is false. Please enter a method."));
	}

}

AActor* UShootingComponent::RayShoot() {

	//Def programming
	if (FirstPersonCamera == NULL || PlayerController == NULL) {
		UE_LOG(LogTemp, Error, TEXT("First Person Camera or PLayer Controller not found in Shooting component."));
		return nullptr;
	}

	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = FirstPersonCamera->GetComponentLocation();
	FVector ForwardVector = FirstPersonCamera->GetForwardVector();

	//Add random bouncing to the ray.
	float BounceX, BounceY, BounceZ;
	BounceX = FMath::RandRange(-BounceGap, BounceGap);
	BounceY = FMath::RandRange(-BounceGap, BounceGap);
	BounceZ = FMath::RandRange(-BounceGap, BounceGap);
	FVector BounceVector = FVector(BounceX, BounceY, BounceZ);
	ForwardVector += BounceVector;

	//Calculate EndTrace and create CQP.
	FVector EndTrace = (ForwardVector * Range) + StartTrace;
	FCollisionQueryParams* CQP = new FCollisionQueryParams();

	//Raycast
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *CQP)) {
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true);
		if (HitResult->GetActor() != NULL) {
			return HitResult->GetActor();
		}
	}
	return nullptr;
}

void UShootingComponent::SpawnProjectile() {
	auto Location = FirstPersonCamera->GetComponentLocation();
	auto ForwardVector = FirstPersonCamera->GetForwardVector();
	float Offset = 100;	//TODO tune offset after.
	Location += (ForwardVector * Offset);

	auto Rotator = FirstPersonCamera->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, Location, Rotator);
	Projectile->LaunchProjectile(ProjectileSpeed);
}

void UShootingComponent::DamageToEnemy(AActor* EnemyToDamage) {
	//Apply damage to enemy.
	if (EnemyToDamage != NULL) {
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);
		EnemyToDamage->TakeDamage(DamageToApply, DamageEvent, UGameplayStatics::GetPlayerController(GetWorld(), 0), GetOwner());
		//If hits enemy charge ultimate.
		if (EnemyToDamage->ActorHasTag(FName("Enemy"))) {
			SkillCaster->ChargeUltimate();
		}
	}
}

void UShootingComponent::PlayFiringSound(){
	//Play firing sound.
	if (FireSound != NULL){
		FVector ActorLocation;
		ActorLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, ActorLocation);
	}
}

void UShootingComponent::PlayFiringAnimation(){
	//Play firing animation.
	if (FireAnimation != NULL){
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL){
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}



//Calls from MakeReadyGunToNextShot method with delay to Handle Firing Rate.
void UShootingComponent::HandleFiringRate() {
	FiringState = EFiringState::READY;
}
//Handles firing rate.
void UShootingComponent::MakeReadyGunToNextShot() {
	FiringState = EFiringState::GETTING_READY;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &UShootingComponent::HandleFiringRate, PrimaryFiringRate, false);
}

//Reloading state. Reload Animation, Sound etc.
void UShootingComponent::ReloadGun() {
	FiringState = EFiringState::RELOADING;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &UShootingComponent::Reload, ReloadingTime, false);
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Reloading Weapon!");
	//TODO implement reload animation.

}

//Reloads bullets and makes ready to next shot.
void UShootingComponent::Reload() {
	CurrentAmmo = TotalAmmo;
	FiringState = EFiringState::READY;
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Gun Reloaded!");
}

void UShootingComponent::SetPlayerIsShooting(bool IsShootingToSet){
	bIsPlayerShooting = IsShootingToSet;
}

void UShootingComponent::SetShootingSkeletalMeshComponent(USkeletalMeshComponent* Mesh) {
	Mesh1P = Mesh;
}
