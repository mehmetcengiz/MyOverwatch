//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "CharacterSkillCaster.h"


// Sets default values for this component's properties
UCharacterSkillCaster::UCharacterSkillCaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UCharacterSkillCaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterSkillCaster::FirePrimary(){
	UE_LOG(LogTemp, Warning, TEXT("Character primary shoot!"));
	OnFirePrimaryCasted.Broadcast();
}

void UCharacterSkillCaster::FireSecondary(){

	float time = FPlatformTime::Seconds();

	//if(bIsFireSecondaryHaveCoolDown && )
	UE_LOG(LogTemp, Warning, TEXT("Character secondary shoot! %f") , time);
	OnFireSecondaryCasted.Broadcast();
}

void UCharacterSkillCaster::AbilityE(){
	UE_LOG(LogTemp, Warning, TEXT("Ability E casted."));
	OnAbilityECasted.Broadcast();
}

void UCharacterSkillCaster::AbilityShift(){
	UE_LOG(LogTemp, Warning, TEXT("Ability Shift"));
	OnAbilityShiftCasted.Broadcast();
}

void UCharacterSkillCaster::AbilityJump(){
	UE_LOG(LogTemp, Warning, TEXT("Ability Jump"));
	OnAbilityJump.Broadcast();
}

void UCharacterSkillCaster::AbilityUltimate(){
	UE_LOG(LogTemp, Warning, TEXT("Ability Ultimate"));
	OnAbilityUltimateCasted.Broadcast();
}



