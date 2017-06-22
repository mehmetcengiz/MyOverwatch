// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "RaycastShootingComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
URaycastShootingComponent::URaycastShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void URaycastShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	

}

void URaycastShootingComponent::SetCameraComponent(UCameraComponent* cameraComponent){
	FirstPersonCamera = cameraComponent;
}

void URaycastShootingComponent::GetCameraComponent(){
	
}

void URaycastShootingComponent::Shoot(){
	UE_LOG(LogTemp, Warning, TEXT("Shoot with raycast!"));

	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = FirstPersonCamera->GetComponentLocation();
	FVector ForwardVector = FirstPersonCamera->GetForwardVector();
	FVector EndTrace = (ForwardVector * Range) + StartTrace;

	UE_LOG(LogTemp, Warning, TEXT("EndTrace: %s"), *EndTrace.ToString());
	FCollisionQueryParams* CQP = new FCollisionQueryParams();

	if(GetWorld()->LineTraceSingleByChannel(*HitResult,StartTrace,EndTrace, ECC_Visibility,*CQP)){
		
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true);

		if(HitResult->GetActor() != NULL){
			UE_LOG(LogTemp, Warning, TEXT("%s TARGET HIT "), *HitResult->GetActor()->GetName());
		}

	}

}
