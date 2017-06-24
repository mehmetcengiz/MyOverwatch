// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API UCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Character base health.
	UPROPERTY(EditDefaultsOnly, Category="Health")
	float Health;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentMaxHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CharacterMaxHealth = 200;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Armor = 0;
	
	

	void TakeDamage(float Damage);
	void Heal(float BonusHealth);
	
};
