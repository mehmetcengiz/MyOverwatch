//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "Soldier76Skills.generated.h"


class URaycastShootingComponent;
class ASoldier76SecondaryProjectile;
class UCharacterSkillCaster;
class ASoldier76Healer;
class ASoldier76Ultimate;
class UShootingComponent;


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

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
	void AbilityShiftPressed();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void AbilityShiftReleased();

	UFUNCTION(BlueprintCallable, Category= "SkillCasting")
	void AbilityJump();

private:
	//Secondary firing.
	UPROPERTY(EditDefaultsOnly)
	float SecondaryProjectileSpeed = 4000;
		
	UPROPERTY()
	UCharacterMovementComponent* MovementComponent = nullptr;

	UPROPERTY()
	UShootingComponent* ShootingComponent = nullptr;

	//For Shift Ability.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float FastRunningSpeed = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DefaultRunningSpeed = 600.0f;

	bool bIsShiftCasted = false;
	void ChangeRunningSpeed(float speed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetMovementComponent(UCharacterMovementComponent* MovementComponentToSet);


protected:
	
	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	UCameraComponent* FirstPersonCamera = nullptr;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly,Category="Firing")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	UAnimMontage* FireAnimation;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY()
	USkeletalMeshComponent* Mesh1P;
	

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASoldier76SecondaryProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASoldier76Healer> SoldierHealerBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class ASoldier76Ultimate> Soldier76UltimateCone;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetShootingSkeletalMeshComponent(USkeletalMeshComponent *Mesh);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCameraComponent(UCameraComponent* CameraToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetShootingComponent(UShootingComponent* ShootingComponentToSet);

	ASoldier76Ultimate* Soldier76Ultimate;
	
};
