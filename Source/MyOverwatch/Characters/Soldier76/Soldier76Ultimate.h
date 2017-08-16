// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "GameFramework/Actor.h"
#include "Soldier76Ultimate.generated.h"

UCLASS()
class MYOVERWATCH_API ASoldier76Ultimate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldier76Ultimate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCameraComponent(UCameraComponent* CameraCompToSet);

private:
	UCameraComponent* CharacterCamera;
	
};
