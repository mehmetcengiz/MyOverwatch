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
	void PlayFiringSound();
	void PlayFiringAnimation();
	void DamageToEnemy(AActor* EnemyToDamage);

	UFUNCTION()
	void Shoot();
	void SetPlayerIsShooting(bool IsShootingToSet);

protected:
	/** Firing state*/
	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	EFiringState FiringState = EFiringState::READY;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float DamageToApply = 40.f;
	/**Realoading Time*/
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadingTime = 2.f;

	/**Firing rate.*/
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float PrimaryFiringRate = 0.10f;
	float LastTimeFired;
	bool bIsPlayerShooting = false;

	/**Magazine settings*/
	UPROPERTY(EditdefaultsOnly, Category = "Firing")
	int32 TotalAmmo = 25;
	int32 CurrentAmmo;

	UPROPERTY(EditdefaultsOnly, Category = "Raycast Firing Type", meta = (EditCondition = "!bEnableProjectileShooting"))
	bool bEnableRayCastShooting = false;
	/** The number of bullet per shot. Example: For heavy weapon might be 1, for shotgun might be 8 */
	UPROPERTY(EditDefaultsOnly, Category = "Raycast Firing Type", meta = (ClampMin = "1", ClampMax = "100", EditCondition = "bEnableRayCastShooting"))
	int32 RayPerShot = 1;
	/** How much bounce for single shot. 0 for no bounce. */
	UPROPERTY(EditDefaultsOnly, Category = "Raycast Firing Type", meta = (ClampMin = "0", ClampMax = "0.5", EditCondition = "bEnableRayCastShooting"))
	float BounceGap = 0.01f;
	/**Range of weapon. */
	UPROPERTY(EditDefaultsOnly, Category = "Raycast Firing Type", meta = (ClampMin = "0", EditCondition = "bEnableRayCastShooting"))
	float Range = 5000.f;

	UPROPERTY(EditdefaultsOnly, Category = "Projectile Firing Type", meta = (EditCondition = "!bEnableRayCastShooting"))
	bool bEnableProjectileShooting = false;
	UPROPERTY(EditdefaultsOnly, Category = "Projectile Firing Type", meta = (EditCondition = "bEnableProjectileShooting"))
	float ProjectileSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Firing Type", meta = (EditCondition = "bEnableProjectileShooting"))
	TSubclassOf<class AProjectile> ProjectileBluePrint;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	UAnimMontage* FireAnimation;



	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY()
	USkeletalMeshComponent* Mesh1P;
	UPROPERTY()
	UCameraComponent* FirstPersonCamera = nullptr;
	UPROPERTY()
	AController* PlayerController = nullptr;
		
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetShootingSkeletalMeshComponent(USkeletalMeshComponent* Mesh);

	
private:
	URaycastShootingComponent* RaycastShooting = nullptr;
	UCharacterSkillCaster* SkillCaster = nullptr;
	

	void MakeReadyGunToNextShot();
	void HandleFiringRate();
	void ReloadGun();
	void Reload();

	AActor* RayShoot();
};
