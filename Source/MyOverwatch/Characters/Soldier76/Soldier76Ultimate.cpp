// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Ultimate.h"
#include "Soldier76Skills.h"


// Sets default values
ASoldier76Ultimate::ASoldier76Ultimate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoldier76Ultimate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoldier76Ultimate::OnComponentOverlap(AActor* OverlapActor){
	//OverlapActor already casted to enemy.
	//UE_LOG(LogTemp, Warning, TEXT("Overlaped actor name: %s"), *OverlapActor->GetName());
	
	CollidedActors.AddUnique(OverlapActor);
}

void ASoldier76Ultimate::OnComponentEndOverlap(AActor* OverlapActor){
	
	CollidedActors.Remove(OverlapActor);
	
}

// Called every frame
void ASoldier76Ultimate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(CharacterCamera != NULL){
		SetActorLocation(CharacterCamera->GetComponentLocation());
		SetActorRotation(CharacterCamera->GetComponentRotation());
	}

}

void ASoldier76Ultimate::SetCameraComponent(UCameraComponent* CameraCompToSet){
	CharacterCamera = CameraCompToSet;
}

AActor* ASoldier76Ultimate::GetEnemiesInCone(){
	
	if(CollidedActors.Num()>0){
		return CollidedActors.Last(0);
	}else{
		return nullptr;
	}
}



