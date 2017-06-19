//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Skills.h"
#include "Engine/Engine.h" //TODO delete later it is for screen debuging.


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
	//TODO Bind the events of player skills.
	
}


// Called every frame
void USoldier76Skills::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void USoldier76Skills::FirePrimaryPressed(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary firePrimary pressed by Soldier76");
}

void USoldier76Skills::FirePrimaryReleased(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary firePrimary released by Soldier76");
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

