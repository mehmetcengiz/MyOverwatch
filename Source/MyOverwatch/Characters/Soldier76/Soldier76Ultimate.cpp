// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Ultimate.h"


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

// Called every frame
void ASoldier76Ultimate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//if(CharacterCamera != NULL){
	//	SetActorLocation(CharacterCamera->GetComponentLocation(), false, nullptr, ETeleportType::None);
	//}
	

}

//void ASoldier76Ultimate::SetCameraComponent(UCameraComponent* CameraCompToSet){
//	CharacterCamera = CameraCompToSet;
//}

