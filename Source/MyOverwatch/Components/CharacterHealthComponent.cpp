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
	Health = CharacterMaxHealth;
	
}


// Called every frame
void UCharacterHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Health <= 0){
		GetOwner()->Destroy();
	}
}

void UCharacterHealthComponent::TakeDamage(float Damage) {

	Health -= Damage;
}

void UCharacterHealthComponent::Heal(float BonusHealth){
	Health += BonusHealth;
}

