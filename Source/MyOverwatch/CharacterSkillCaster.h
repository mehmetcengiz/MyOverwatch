//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterSkillCaster.generated.h"

class UCharacterSkills;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSecondaryCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirePrimaryCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityECasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityUltimateCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityShiftCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityJump);


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


	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFirePrimaryCasted OnFirePrimaryCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFireSecondaryCasted OnFireSecondaryCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityECasted OnAbilityECasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityUltimateCasted OnAbilityUltimateCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityShiftCasted OnAbilityShiftCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityJump OnAbilityJump;


	

};
