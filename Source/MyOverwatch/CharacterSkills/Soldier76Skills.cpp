//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Skills.h"
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
	
	//TODO Bind the events of player skills.
	
}


// Called every frame
void USoldier76Skills::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if(bIsPlayerShooting){
		if(FiringState == EFiringState::READY){
			Shoot();
		}
	}

	if(FiringState == EFiringState::NOT_READY){
		//TODO something wrong here.
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &USoldier76Skills::MakeReadyGunToNextShot, false);
	}

}


void USoldier76Skills::Shoot(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Soldier76 is Shooting !! ");
	FiringState = EFiringState::NOT_READY;
}


void USoldier76Skills::FirePrimaryPressed(){
	bIsPlayerShooting = true;
}

void USoldier76Skills::FirePrimaryReleased(){
	bIsPlayerShooting = false;
}

void USoldier76Skills::MakeReadyGunToNextShot(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Gun is NOT READY ");
	
	if(FiringState == EFiringState::NOT_READY){
		FiringState = EFiringState::READY;
	}
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


