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
	/** The number of bullet per shot. Example: For heavy weapon might be 1, for shotgun might be 8 */
	UPROPERTY(EditDefaultsOnly,Category = "Setup", meta = (ClampMin = "1", ClampMax = "100"))
	int32 RayPerShot =1;

	/** How much bounce for single shot. 0 for no bounce. */
	UPROPERTY(EditDefaultsOnly,Category ="Setup", meta = (ClampMin = "0", ClampMax = "0.5"))
	float BounceGap = 0.01f;

	/**Range of weapon. */
	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (ClampMin = "0"))
	float Range = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float DamageToApply = 40.f ;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCameraComponent(UCameraComponent* cameraComponent);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerController(AController* controller);

	bool Shoot();

private:
	UPROPERTY()
	UCameraComponent* FirstPersonCamera = nullptr;

	UPROPERTY()
	AController* PlayerController = nullptr;


	
	
};
