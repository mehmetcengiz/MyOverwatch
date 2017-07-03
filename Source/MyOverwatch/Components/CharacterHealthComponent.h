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
private:
	//Character base health.
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentMaxHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CharacterMaxHealth = 200;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Armor = 0;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentMaxHealth();
	
	
	

	void TakeDamage(float Damage);
	void Heal(float BonusHealth);

};
