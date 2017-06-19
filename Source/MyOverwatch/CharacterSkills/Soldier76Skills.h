//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "Soldier76Skills.generated.h"

UENUM()
enum class EFiringState : uint8{
	FIRING, 
	OUT_OF_AMMO,
	RELOADING,
	READY, 
	NOT_READY
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API USoldier76Skills : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoldier76Skills();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Shoot();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void FirePrimaryPressed();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void FirePrimaryReleased();
	
	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void FireSecondary();
	
	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void AbilityE();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void AbilityUltimate();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void AbilityShift();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void AbilityJump();

private:
	//Primary firing.
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float PrimaryFiringRate =0.3;
	float LastTimeFired;
	bool bIsPlayerShooting;

	void MakeReadyGunToNextShot();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::READY;


};
