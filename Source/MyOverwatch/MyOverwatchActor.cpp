// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "./Components/CharacterHealthComponent.h"
#include "MyOverwatchActor.h"

// Sets default values
AMyOverwatchActor::AMyOverwatchActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyOverwatchActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyOverwatchActor::SetCharacterHealthComponent(UCharacterHealthComponent* CharacterHealth){
	CharacterHealthComponent = CharacterHealth;
}

float AMyOverwatchActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	
	if(CharacterHealthComponent){
		CharacterHealthComponent->TakeDamage(Damage);
	}

	return Damage;

}

