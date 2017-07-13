// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "GameFramework/Actor.h"
#include "Soldier76Healer.generated.h"

class AMyOverwatchCharacter;

UENUM()
enum class EHealingState : uint8{
	READY,
	HEALING,
	GETTING_READY
};

UCLASS()
class MYOVERWATCH_API ASoldier76Healer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldier76Healer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	bool bHealActors = false;
	
	EHealingState HealingState = EHealingState::READY;

	void HandleHealingRate();
	void GetReadyToNextHeal();
	void DestroyObject();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AMyOverwatchCharacter* OverlapedActor = nullptr;
	
	void HealActorsEveryTick();

	UFUNCTION(BlueprintCallable, Category = "Overlap")
	void StartHealActor(AActor* OverlapedActorToHeal);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
	void EndHealActor();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void DestroyAfterTime();


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float HealBonus = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TotalHealingTimeAfterSpawn = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float HealingRate = 0.25f;



};
