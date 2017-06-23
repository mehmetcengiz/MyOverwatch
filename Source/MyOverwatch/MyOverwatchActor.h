// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "GameFramework/Actor.h"
#include "MyOverwatchActor.generated.h"

class UCharacterHealthComponent;

UCLASS()
class MYOVERWATCH_API AMyOverwatchActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyOverwatchActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UCharacterHealthComponent* CharacterHealthComponent;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCharacterHealthComponent(UCharacterHealthComponent* CharacterHealth);
};
