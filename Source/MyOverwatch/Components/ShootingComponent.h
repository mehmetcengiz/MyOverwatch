// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "ShootingComponent.generated.h"

class URaycastShootingComponent;
class UCharacterSkillCaster;

UENUM()
enum class EFiringState : uint8 {
	READY,
	FIRING,
	NOT_READY,
	GETTING_READY,
	OUT_OF_AMMO,
	RELOADING
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Shoot();

	void SetPlayerIsShooting(bool IsShootingToSet);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	EFiringState FiringState = EFiringState::READY;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float DamageToApply = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadingRate = 2.f;

	
	//Primary firing.
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float PrimaryFiringRate = 0.10f;
	float LastTimeFired;
	bool bIsPlayerShooting = false;

	//Magazine settings.
	UPROPERTY(EditdefaultsOnly, Category = "Firing")
	int32 TotalAmmo = 25;
	int32 CurrentAmmo;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetRaycastShootingComponent(URaycastShootingComponent* RaycastToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCharacterSkillCaster(UCharacterSkillCaster* SkillCasterToSet);

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	UAnimMontage* FireAnimation;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY()
	USkeletalMeshComponent* Mesh1P;
	
private:
	URaycastShootingComponent* RaycastShooting = nullptr;

	UCharacterSkillCaster* SkillCaster = nullptr;

	void MakeReadyGunToNextShot();
	void HandleFiringRate();
	void ReloadGun();
	void Reload();
};
