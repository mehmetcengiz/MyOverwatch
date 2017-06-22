//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Skills.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h" //TODO delete later it is for screen debuging.

#define OUT

// Sets default values for this component's properties
USoldier76Skills::USoldier76Skills()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	
	if(bIsPlayerShooting && FiringState == EFiringState::READY){ Shoot();}
	
	if(FiringState == EFiringState::NOT_READY){ HandleFiringRate();	}

	if (FiringState == EFiringState::OUT_OF_AMMO) { ReloadGun(); }

}


void USoldier76Skills::Shoot(){
	
	FiringState = EFiringState::NOT_READY;

	//TODO implement shooting.

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
	FString ShootingMessage(TEXT("Shooting!! Bullet Left: "));
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red,ShootingMessage + FString::FromInt(CurrentAmmo));
}


void USoldier76Skills::FirePrimaryPressed(){
	bIsPlayerShooting = true;
}

void USoldier76Skills::FirePrimaryReleased(){
	bIsPlayerShooting = false;
}

void USoldier76Skills::MakeReadyGunToNextShot(){
	FiringState = EFiringState::READY;
}

void USoldier76Skills::HandleFiringRate() {
	FiringState = EFiringState::GETTING_READY;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &USoldier76Skills::MakeReadyGunToNextShot, PrimaryFiringRate, false);
}

void USoldier76Skills::ReloadGun(){
	FiringState = EFiringState::RELOADING;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &USoldier76Skills::Reload, ReloadingRate, false);
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Reloading Weapon!");
	//TODO implement reload animation.

}

void USoldier76Skills::Reload(){
	CurrentAmmo = TotalAmmo;
	FiringState = EFiringState::READY;
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Gun Reloaded!");
}

void USoldier76Skills::FireSecondary(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary fireSecondary casted by Soldier76");
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


