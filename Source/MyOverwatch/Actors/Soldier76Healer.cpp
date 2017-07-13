// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "MyOverwatchCharacter.h"
#include "Components/CharacterHealthComponent.h"
#include "Soldier76Healer.h"


// Sets default values
ASoldier76Healer::ASoldier76Healer(){
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoldier76Healer::BeginPlay(){
	Super::BeginPlay();
	DestroyAfterTime();
}

// Called every frame
void ASoldier76Healer::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (HealingState == EHealingState::READY && bHealActors){
		HealActorsEveryTick();
	}
	if (HealingState == EHealingState::HEALING){
		HandleHealingRate();
	}

}

void ASoldier76Healer::HealActorsEveryTick(){

	HealingState = EHealingState::HEALING;
	if (OverlapedActor){
		auto OverlapedHealthComponent = OverlapedActor->GetCharacterHealthComponent();
		OverlapedHealthComponent->Heal(HealBonus);
	}
}

void ASoldier76Healer::HandleHealingRate() {
	HealingState = EHealingState::GETTING_READY;
	
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &ASoldier76Healer::GetReadyToNextHeal, HealingRate, false);

}

void ASoldier76Healer::GetReadyToNextHeal(){
	HealingState = EHealingState::READY;
}


void ASoldier76Healer::DestroyAfterTime(){
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &ASoldier76Healer::DestroyObject, TotalHealingTimeAfterSpawn, false);
}

void ASoldier76Healer::DestroyObject() {
	Destroy();
}

void ASoldier76Healer::StartHealActor(AActor* OverlapedActorToHeal){
	UE_LOG(LogTemp, Warning, TEXT("Heal function is working!"));
	OverlapedActor = static_cast<AMyOverwatchCharacter*>(OverlapedActorToHeal);
	bHealActors = true;
}

void ASoldier76Healer::EndHealActor(){
	UE_LOG(LogTemp, Warning, TEXT("Heal Ending"));
	bHealActors = false;
}
