// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "CharacterHealthComponent.h"


// Sets default values for this component's properties
UCharacterHealthComponent::UCharacterHealthComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCharacterHealthComponent::BeginPlay(){
	Super::BeginPlay();
	CurrentMaxHealth = CharacterMaxHealth;
	CurrentHealth = CharacterMaxHealth;
	
}


// Called every frame
void UCharacterHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentMaxHealth = CharacterMaxHealth + Armor;
	if(CurrentHealth <= 0){
		GetOwner()->Destroy();
	}
}

float UCharacterHealthComponent::GetCurrentHealth(){
	return CurrentHealth;
}

float UCharacterHealthComponent::GetCurrentMaxHealth(){
	return CurrentMaxHealth;
}

void UCharacterHealthComponent::TakeDamage(float Damage) {
	CurrentHealth -= Damage;
}

void UCharacterHealthComponent::Heal(float BonusHealth){
	CurrentHealth += BonusHealth;
}

