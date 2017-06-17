//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterSkillCaster.generated.h"

class UCharacterSkills;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSecondaryCasted);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API UCharacterSkillCaster : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterSkillCaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void FirePrimary();
	void FireSecondary();
	void AbilityE();
	void AbilityShift();
	void AbilityJump();
	void AbilityUltimate();

	UPROPERTY(EditDefaultsOnly, Category = "Character Setup")
	UCharacterSkills *characterSkills;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFireSecondaryCasted OnFireSecondaryCasted;

};
