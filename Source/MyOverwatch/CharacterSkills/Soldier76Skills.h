//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "Soldier76Skills.generated.h"


class URaycastShootingComponent;
class ASoldier76PrimaryProjectile;
class UCharacterSkillCaster;

UENUM()
enum class EFiringState : uint8{
	READY,
	FIRING, 
	NOT_READY,
	GETTING_READY,
	OUT_OF_AMMO,
	RELOADING
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

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShootPrimary();

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
	float PrimaryFiringRate =0.10f;
	float LastTimeFired;
	bool bIsPlayerShooting;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadingRate = 2.f;

	void MakeReadyGunToNextShot();
	void HandleFiringRate();
	void ReloadGun();
	void Reload();

	//Secondary firing.
	UPROPERTY(EditDefaultsOnly)
	float SecondaryProjectileSpeed = 4000;

	//Magazine settings.
	UPROPERTY(EditdefaultsOnly, Category = "Firing")
	int32 TotalAmmo = 25;
	int32 CurrentAmmo;

	UPROPERTY()
	URaycastShootingComponent* RaycastShooting = nullptr;

	UPROPERTY(EditdefaultsOnly, Category = "Firing")
	UCharacterSkillCaster* SkillCaster = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::READY;
	
	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	UCameraComponent* FirstPersonCamera = nullptr;

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly,Category="Firing")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	UAnimMontage* FireAnimation;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY()
	USkeletalMeshComponent* Mesh1P;
	


	
	
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int32 GetTotalAmmo();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int32 GetCurrentAmmo();
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASoldier76PrimaryProjectile> ProjectileBluePrint;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetShootingSkeletalMeshComponent(USkeletalMeshComponent *Mesh);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetRaycastShootingComponent(URaycastShootingComponent *Raycast);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCameraComponent(UCameraComponent* ProjectileToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCharacterSkillCaster(UCharacterSkillCaster* SkillCasterToSet);


};
