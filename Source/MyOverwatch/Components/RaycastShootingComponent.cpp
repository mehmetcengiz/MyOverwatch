// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "RaycastShootingComponent.h"


// Sets default values for this component's properties
URaycastShootingComponent::URaycastShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void URaycastShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void URaycastShootingComponent::Shooting(){
	UE_LOG(LogTemp, Warning, TEXT("Shooting with raycast!"));
}