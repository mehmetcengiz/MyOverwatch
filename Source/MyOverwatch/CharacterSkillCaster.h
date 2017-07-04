//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterSkillCaster.generated.h"

class UCharacterSkills;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirePrimaryPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirePrimaryReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSecondaryPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSecondaryReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityECasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityUltimateCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityShiftCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityJump);


UENUM()
enum class ESkillCastingState : uint8{
	HAS_NO_COOLDOWN,
	READY,
	ON_COOLDOWN
};

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

private:	
	
	//Skill cooldown setups.
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	bool bIsFireSecondaryHaveCoolDown = true;
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup", meta = (EditCondition = "bIsFireSecondaryHaveCoolDown"))
	float FireSecondaryCoolDownTime = 3.0f;
	float LastTimeFireSecondaryCasted = 0;
	ESkillCastingState FireSecondaryCastingState = ESkillCastingState::READY;

	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	bool bIsAbilityEHaveCoolDown = true;
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup", meta = (EditCondition = "bIsAbilityEHaveCoolDown"))
	float AbilityECoolDownTime = 3.0f;
	float LastTimeAbilityECasted = 0;
	ESkillCastingState AbilityECastingState = ESkillCastingState::READY;


	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	bool bIsAbilityShiftHaveCoolDown = true;
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup", meta = (EditCondition = "bIsAbilityShiftHaveCoolDown"))
	float AbilityShiftCoolDownTime = 3.0f;
	float LastTimeAbilityShiftCasted = 0;
	ESkillCastingState AbilityShiftCastingState = ESkillCastingState::READY;


	//Maximum charge for ultimate.
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	int32 AbilityUltimateMaxCharge = 100;
	int32 CurrentUltimateCharge = 0;

public:
	//Called when any skill casted.
	void FirePrimaryPressed();
	void FirePrimaryReleased();
	void FireSecondaryPressed();
	void FireSecondaryReleased();
	void AbilityE();
	void AbilityShift();
	void AbilityJump();
	void AbilityUltimate();


	//When any skill casted those event will be broadcasted.
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFirePrimaryPressed OnFirePrimaryPressed;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFirePrimaryReleased OnFirePrimaryReleased;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFireSecondaryPressed OnFireSecondaryPressed;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnFireSecondaryReleased OnFireSecondaryReleased;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityECasted OnAbilityECasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityUltimateCasted OnAbilityUltimateCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityShiftCasted OnAbilityShiftCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityJump OnAbilityJump;

	//Ability cooldowns for UI
	UFUNCTION(BlueprintCallable, Category="Cooldown")
	int32 GetFireSecondaryCoolDown();
	
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	ESkillCastingState GetFireSecondarySkillState();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	int32 GetAbilityECoolDown();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	ESkillCastingState GetAbilityESkillState();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	int32 GetAbilityShiftCoolDown();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	ESkillCastingState GetAbilityShiftSkillState();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	int32 GetCurrentUltimateCharge();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	int32 GetMaxUltimateCharge();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ChargeUltimate();

	
	

};
