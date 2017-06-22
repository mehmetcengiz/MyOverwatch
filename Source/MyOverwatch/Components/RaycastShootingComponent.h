// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "RaycastShootingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API URaycastShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URaycastShootingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
		
	void Shooting();
	
};
