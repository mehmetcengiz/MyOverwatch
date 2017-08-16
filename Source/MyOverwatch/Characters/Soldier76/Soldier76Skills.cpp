//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Skills.h"
#include "./Components/RaycastShootingComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h" //TODO delete later it is for screen debuging.
#include "CharacterSkillCaster.h"
#include "./Characters/Soldier76/Soldier76SecondaryProjectile.h"
#include "./Characters/Soldier76/Soldier76Healer.h"
#include "./Characters/Soldier76/Soldier76Ultimate.h"

#define OUT

// Sets default values for this component's properties
USoldier76Skills::USoldier76Skills(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USoldier76Skills::BeginPlay(){
	Super::BeginPlay();
	bIsPlayerShooting = false;
	CurrentAmmo = TotalAmmo;

	//TODO Bind the events of player skills.

}


// Called every frame
void USoldier76Skills::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bIsPlayerShooting && FiringState == EFiringState::READY && !bIsShiftCasted){ ShootPrimary(); }

	if (FiringState == EFiringState::NOT_READY){ MakeReadyGunToNextShot(); }

	if (FiringState == EFiringState::OUT_OF_AMMO){ ReloadGun(); }


}


void USoldier76Skills::ShootPrimary(){

	FiringState = EFiringState::NOT_READY;
	

	
	//If no bullet change firing state to Out_Of_Ammo.
	if (CurrentAmmo <= 0){
		FiringState = EFiringState::OUT_OF_AMMO;
		return;
	}
	CurrentAmmo--;

	// Cast a ray. If hits something charge ultimate.
	if (RaycastShooting != NULL){
		if (RaycastShooting->Shoot()){
			if (SkillCaster != NULL){
				SkillCaster->ChargeUltimate();
			}
		}
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

//Soldier76 keeps shooting when player keep pressing button.
void USoldier76Skills::FirePrimaryPressed(){
	bIsPlayerShooting = true;
}

//Soldier76 stops shooting when player released button.
void USoldier76Skills::FirePrimaryReleased(){
	bIsPlayerShooting = false;
}

//Calls from MakeReadyGunToNextShot method with delay to Handle Firing Rate.
void USoldier76Skills::HandleFiringRate(){
	FiringState = EFiringState::READY;
}

//Handles firing rate.
void USoldier76Skills::MakeReadyGunToNextShot(){
	FiringState = EFiringState::GETTING_READY;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &USoldier76Skills::HandleFiringRate, PrimaryFiringRate, false);
}

//Reloading state. Reload Animation, Sound etc.
void USoldier76Skills::ReloadGun(){
	FiringState = EFiringState::RELOADING;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &USoldier76Skills::Reload, ReloadingRate, false);
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Reloading Weapon!");
	//TODO implement reload animation.

}

//Reloads bullets and makes ready to next shot.
void USoldier76Skills::Reload(){
	CurrentAmmo = TotalAmmo;
	FiringState = EFiringState::READY;
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Gun Reloaded!");
}

void USoldier76Skills::FireSecondary(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary fireSecondary casted by Soldier76");

	if (FirstPersonCamera == NULL) { return; }

	auto Location = FirstPersonCamera->GetComponentLocation();
	auto ForwardVector = FirstPersonCamera->GetForwardVector();
	float Offset = 100;	//TODO tune offset after.
	Location += (ForwardVector * Offset);

	auto Rotator = FirstPersonCamera->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<ASoldier76SecondaryProjectile>(ProjectileBluePrint, Location, Rotator);
	Projectile->LaunchProjectile(SecondaryProjectileSpeed);

	//Firing sound.
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

void USoldier76Skills::AbilityE(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary E casted by Soldier76");

	auto CharacterLocation = GetOwner()->GetActorLocation();
	FVector Location = FVector(CharacterLocation.X, CharacterLocation.Y, 170.f);	
	auto HeallerActor = GetWorld()->SpawnActor<ASoldier76Healer>(SoldierHealerBluePrint, Location, FRotator(0, 0, 0));




}

void USoldier76Skills::AbilityUltimate(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary Q casted by Soldier76");
	
	if(FirstPersonCamera == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Camera component is null."));
		return;
	}

	auto Location = FirstPersonCamera->GetComponentLocation();
	auto Rotator = FirstPersonCamera->GetComponentRotation();

	auto UltimateCone = GetWorld()->SpawnActor<ASoldier76Ultimate>(Soldier76UltimateCone, Location, Rotator);
	

}

void USoldier76Skills::AbilityShiftPressed(){
	bIsShiftCasted = true;
	ChangeRunningSpeed(FastRunningSpeed);
}

void USoldier76Skills::AbilityShiftReleased(){
	bIsShiftCasted = false;
	ChangeRunningSpeed(DefaultRunningSpeed);
}

void USoldier76Skills::AbilityJump(){
}

void USoldier76Skills::SetShootingSkeletalMeshComponent(USkeletalMeshComponent* Mesh){
	Mesh1P = Mesh;
}

void USoldier76Skills::SetRaycastShootingComponent(URaycastShootingComponent* Raycast){
	RaycastShooting = Raycast;
}

void USoldier76Skills::ChangeRunningSpeed(float speed){
	MovementComponent->MaxWalkSpeed = speed;
}

void USoldier76Skills::SetMovementComponent(UCharacterMovementComponent* MovementComponentToSet){
	MovementComponent = MovementComponentToSet;
}

int32 USoldier76Skills::GetTotalAmmo(){
	return TotalAmmo;
}

int32 USoldier76Skills::GetCurrentAmmo(){
	return CurrentAmmo;
}

void USoldier76Skills::SetCameraComponent(UCameraComponent* CameraToSet){
	FirstPersonCamera = CameraToSet;
}

void USoldier76Skills::SetCharacterSkillCaster(UCharacterSkillCaster* SkillCasterToSet){
	SkillCaster = SkillCasterToSet;
}
