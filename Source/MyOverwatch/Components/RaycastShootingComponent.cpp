// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "RaycastShootingComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/DamageType.h"


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

void URaycastShootingComponent::SetPlayerController(AController* controller){
	PlayerController = controller;
}

bool URaycastShootingComponent::Shoot(){

	//For multiple bullet increase RayPerShot.
	for (int32 i = 0; i<RayPerShot;i++){
				
		//Get StartTrace and Forward Vector
		FHitResult* HitResult = new FHitResult();
		if (FirstPersonCamera == NULL) { return false; }
		FVector StartTrace = FirstPersonCamera->GetComponentLocation();
		FVector ForwardVector = FirstPersonCamera->GetForwardVector();
	
		//Add random bouncing to the ray.
		float BounceX, BounceY,BounceZ;
		BounceX = FMath::RandRange(-BounceGap, BounceGap);
		BounceY = FMath::RandRange(-BounceGap, BounceGap);
		BounceZ = FMath::RandRange(-BounceGap, BounceGap);
		FVector BounceVector = FVector(BounceX, BounceY, BounceZ);
		ForwardVector += BounceVector;

		//Calculate EndTrace and create CQP.
		FVector EndTrace = (ForwardVector * Range) + StartTrace;
		FCollisionQueryParams* CQP = new FCollisionQueryParams();

		//Raycast
		if(GetWorld()->LineTraceSingleByChannel(*HitResult,StartTrace,EndTrace, ECC_Visibility,*CQP)){
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true);
			if(HitResult->GetActor() != NULL){
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				FDamageEvent DamageEvent(ValidDamageTypeClass);

				if (PlayerController == NULL) { return false; }
				HitResult->GetActor()->TakeDamage(DamageToApply, DamageEvent, PlayerController,GetOwner());
				
				UE_LOG(LogTemp, Warning, TEXT("%s TARGET HIT "), *HitResult->GetActor()->GetName());
				return true;
			}
		}
	}
	return false;
}
