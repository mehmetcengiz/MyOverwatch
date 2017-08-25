// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "ShootingComponent.h"
#include "./Components/RaycastShootingComponent.h"
#include "CharacterSkillCaster.h"

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
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bIsPlayerShooting && FiringState == EFiringState::READY /*&& !bIsShiftCasted*/) { Shoot(); }

	if (FiringState == EFiringState::NOT_READY) { MakeReadyGunToNextShot(); }

	if (FiringState == EFiringState::OUT_OF_AMMO) { ReloadGun(); }


}

void UShootingComponent::Shoot(){

	FiringState = EFiringState::NOT_READY;


	//If no bullet change firing state to Out_Of_Ammo.
	if (CurrentAmmo <= 0){
		FiringState = EFiringState::OUT_OF_AMMO;
		return;
	}
	CurrentAmmo--;


	//Get shooted enemy.
	AActor* EnemyToDamage = nullptr;

	if (RaycastShooting != NULL){
		if (RaycastShooting->Shoot() && SkillCaster != NULL){
			EnemyToDamage = RaycastShooting->GetEnemyToHit();
			SkillCaster->ChargeUltimate();
		}
	}

	//Apply damage to enemy.
	if (EnemyToDamage != NULL){
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);
		EnemyToDamage->TakeDamage(DamageToApply, DamageEvent, UGameplayStatics::GetPlayerController(GetWorld(), 0), GetOwner());
	}


	//Play firing sound.
	if (FireSound != NULL){
		FVector ActorLocation;
		ActorLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, ActorLocation);
	}

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
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &UShootingComponent::Reload, ReloadingRate, false);
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

void UShootingComponent::SetRaycastShootingComponent(URaycastShootingComponent* RaycastToSet){
	RaycastShooting = RaycastToSet;
}

void UShootingComponent::SetCharacterSkillCaster(UCharacterSkillCaster* SkillCasterToSet){ }
