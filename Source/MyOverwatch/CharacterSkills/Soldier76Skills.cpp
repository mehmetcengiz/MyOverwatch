//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Skills.h"
#include "Components/RaycastShootingComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h" //TODO delete later it is for screen debuging.
#include "Projectiles/Soldier76PrimaryProjectile.h"

#define OUT

// Sets default values for this component's properties
USoldier76Skills::USoldier76Skills()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USoldier76Skills::BeginPlay()
{
	Super::BeginPlay();
	bIsPlayerShooting = false;
	CurrentAmmo = TotalAmmo;
	
	//TODO Bind the events of player skills.
	
}




// Called every frame
void USoldier76Skills::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if(bIsPlayerShooting && FiringState == EFiringState::READY){ ShootPrimary();}
	
	if(FiringState == EFiringState::NOT_READY){ HandleFiringRate();	}

	if (FiringState == EFiringState::OUT_OF_AMMO) { ReloadGun(); }

}


void USoldier76Skills::ShootPrimary(){
	
	FiringState = EFiringState::NOT_READY;

	//TODO implement shooting.
	if(RaycastShooting != NULL){
		RaycastShooting->Shoot();
	}
	

	//If no bullet change firing state to Out_Of_Ammo.
	if(CurrentAmmo <=0){
		FiringState = EFiringState::OUT_OF_AMMO;
		return;
	}
	CurrentAmmo--;

	//Play firing sound.
	if(FireSound != NULL){
		FVector ActorLocation;
		ActorLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, ActorLocation);
	}

	//Play firing animation.
	if(FireAnimation != NULL){
		UAnimInstance * AnimInstance = Mesh1P->GetAnimInstance();
		if(AnimInstance != NULL){
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	//Print current bullet on screen.
	FString ShootingMessage(TEXT("Shoot!! Bullet Left: "));
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red,ShootingMessage + FString::FromInt(CurrentAmmo));
}

//Soldier76 keeps shooting when player keep pressing button.
void USoldier76Skills::FirePrimaryPressed(){
	bIsPlayerShooting = true;
}

//Soldier76 stops shooting when player released button.
void USoldier76Skills::FirePrimaryReleased(){
	bIsPlayerShooting = false;
}

//Calls MakeReadyGunToNextShot method with delay to Handle Firing Rate.
void USoldier76Skills::HandleFiringRate() {
	FiringState = EFiringState::GETTING_READY;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &USoldier76Skills::MakeReadyGunToNextShot, PrimaryFiringRate, false);
}

//Used for firing rate by HandleFiringRate method.
void USoldier76Skills::MakeReadyGunToNextShot(){
	FiringState = EFiringState::READY;
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

	auto Location = FirstPersonCamera->GetComponentLocation();
	auto Rotator = FirstPersonCamera->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<ASoldier76PrimaryProjectile>(ProjectileBluePrint, Location, Rotator);


}

void USoldier76Skills::AbilityE(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary E casted by Soldier76");
}

void USoldier76Skills::AbilityUltimate(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary Q casted by Soldier76");
}
void USoldier76Skills::AbilityShift(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary Shift casted by Soldier76");
}
void USoldier76Skills::AbilityJump(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary Jump casted by Soldier76");
}

void USoldier76Skills::SetShootingSkeletalMeshComponent(USkeletalMeshComponent* Mesh) {
	Mesh1P = Mesh;
}

void USoldier76Skills::SetRaycastShootingComponent(URaycastShootingComponent* Raycast){
	RaycastShooting = Raycast;
}

void USoldier76Skills::SetCameraComponent(UCameraComponent* CameraToSet){
	FirstPersonCamera = CameraToSet;
}
