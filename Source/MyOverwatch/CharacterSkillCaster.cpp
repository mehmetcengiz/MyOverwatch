//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "CharacterSkillCaster.h"


// Sets default values for this component's properties
UCharacterSkillCaster::UCharacterSkillCaster(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts
void UCharacterSkillCaster::BeginPlay(){
	Super::BeginPlay();

}

void UCharacterSkillCaster::FirePrimaryPressed(){
	UE_LOG(LogTemp, Warning, TEXT("Character primary pressed shoot!"));
	OnFirePrimaryPressed.Broadcast();
}

void UCharacterSkillCaster::FirePrimaryReleased(){
	UE_LOG(LogTemp, Warning, TEXT("Character primary Relaesed"));
	OnFirePrimaryReleased.Broadcast();
}

void UCharacterSkillCaster::FireSecondary(){

	if (!bIsFireSecondaryHaveCoolDown || FPlatformTime::Seconds() - LastTimeFireSecondaryCasted > FireSecondaryCoolDownTime){
		UE_LOG(LogTemp, Warning, TEXT("Character secondary shoot! %f"));
		LastTimeFireSecondaryCasted = FPlatformTime::Seconds();
		OnFireSecondaryCasted.Broadcast();
	}else {
		float cooldown = FireSecondaryCoolDownTime + LastTimeFireSecondaryCasted - FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Secondary Fire is in cooldown %f"), cooldown);
	}
}

void UCharacterSkillCaster::AbilityE(){

	if(!bIsAbilityEHaveCoolDown || FPlatformTime::Seconds() - LastTimeAbilityECasted > AbilityECoolDownTime){
		UE_LOG(LogTemp, Warning, TEXT("Ability E casted."));
		LastTimeAbilityECasted = FPlatformTime::Seconds();
		OnAbilityECasted.Broadcast();
	}else{
		float cooldown = AbilityECoolDownTime + LastTimeAbilityECasted - FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Ability E is on cooldown %f"), cooldown);
	}
}

void UCharacterSkillCaster::AbilityShift(){

	if(!bIsAbilityShiftHaveCoolDown || FPlatformTime::Seconds()- LastTimeAbilityShiftCasted > AbilityShiftCoolDownTime){
		UE_LOG(LogTemp, Warning, TEXT("Ability Shift"));
		OnAbilityShiftCasted.Broadcast();
		LastTimeAbilityShiftCasted = FPlatformTime::Seconds();
	}else{
		float cooldown = AbilityShiftCoolDownTime + LastTimeAbilityShiftCasted - FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Ability Shift is on cooldown %f"), cooldown);
	}

}

void UCharacterSkillCaster::AbilityJump(){
	UE_LOG(LogTemp, Warning, TEXT("Ability Jump"));
	OnAbilityJump.Broadcast();
}

void UCharacterSkillCaster::AbilityUltimate(){

	if(CurrentUltimateCharge >= AbilityUltimateChargeMax){
		UE_LOG(LogTemp, Warning, TEXT("Ability Ultimate"));
		OnAbilityUltimateCasted.Broadcast();
		CurrentUltimateCharge = 0;
	}
}
