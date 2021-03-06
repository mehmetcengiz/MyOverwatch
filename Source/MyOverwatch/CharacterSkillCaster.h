//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterSkillCaster.generated.h"

class UCharacterSkills;

//Delegates for casting skills.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirePrimaryPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirePrimaryReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSecondaryPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSecondaryReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityUltimateCasted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityShiftPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityShiftReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityJumpPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityJumpReleased);


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
	
	/*Secondary Fire cooldown setups.*/
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	bool bIsFireSecondaryHaveCoolDown = true;

	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup", meta = (EditCondition = "bIsFireSecondaryHaveCoolDown"))
	float FireSecondaryCoolDownTime = 3.0f;

	float LastTimeFireSecondaryCasted = 0;
	ESkillCastingState FireSecondaryCastingState = ESkillCastingState::READY;

	/*Ability E Cooldown setups.*/
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	bool bIsAbilityEHaveCoolDown = true;
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup", meta = (EditCondition = "bIsAbilityEHaveCoolDown"))
	float AbilityECoolDownTime = 3.0f;
	float LastTimeAbilityECasted = 0;
	ESkillCastingState AbilityECastingState = ESkillCastingState::READY;

	/*Ability Shift Cooldown setups*/
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	bool bIsAbilityShiftHaveCoolDown = true;
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup", meta = (EditCondition = "bIsAbilityShiftHaveCoolDown"))
	float AbilityShiftCoolDownTime = 3.0f;
	float LastTimeAbilityShiftCasted = 0;
	ESkillCastingState AbilityShiftCastingState = ESkillCastingState::READY;


	/*Ultimate setups*/
	UPROPERTY(EditDefaultsOnly, Category = "SkillSetup")
	int32 AbilityUltimateMaxCharge = 100;
	int32 CurrentUltimateCharge = 0;
public:

	//Called when any skill casted.
	void FirePrimaryPressed();
	void FirePrimaryReleased();
	void FireSecondaryPressed();
	void FireSecondaryReleased();
	void AbilityEPressed();
	void AbilityEReleased();
	void AbilityShiftPressed();
	void AbilityShiftReleased();
	void AbilityJumpPressed();
	void AbilityJumpReleased();
	void AbilityUltimate();

private:
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
	FOnAbilityEPressed OnAbilityEPressed;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityEReleased OnAbilityEReleased;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityUltimateCasted OnAbilityUltimateCasted;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityShiftPressed OnAbilityShiftPressed;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityShiftReleased OnAbilityShiftReleased;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityJumpPressed OnAbilityJumpPressed;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnAbilityJumpReleased OnAbilityJumpReleased;

public:

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
