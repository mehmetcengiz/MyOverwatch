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

	if (!bIsFireSecondaryHaveCoolDown) { FireSecondaryCastingState = ESkillCastingState::HAS_NO_COOLDOWN; }

}

void UCharacterSkillCaster::FirePrimaryPressed(){
	OnFirePrimaryPressed.Broadcast();
}

void UCharacterSkillCaster::FirePrimaryReleased(){
	OnFirePrimaryReleased.Broadcast();
}

void UCharacterSkillCaster::FireSecondaryPressed(){

	if (!bIsFireSecondaryHaveCoolDown || FPlatformTime::Seconds() - LastTimeFireSecondaryCasted > FireSecondaryCoolDownTime){
		UE_LOG(LogTemp, Warning, TEXT("Character secondary shoot! %f"));
		LastTimeFireSecondaryCasted = FPlatformTime::Seconds();
		OnFireSecondaryPressed.Broadcast();
	}else {
		float cooldown = FireSecondaryCoolDownTime + LastTimeFireSecondaryCasted - FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Secondary Fire is in cooldown %f"), cooldown);
	}
}

void UCharacterSkillCaster::FireSecondaryReleased() {
	OnFireSecondaryReleased.Broadcast();
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

int32 UCharacterSkillCaster::GetFireSecondaryCoolDown(){
	if (FireSecondaryCastingState == ESkillCastingState::HAS_NO_COOLDOWN) { return -1; } // If has no cooldown return -1

	float TimeLeft = FPlatformTime::Seconds() - LastTimeFireSecondaryCasted;
	
	if(TimeLeft > FireSecondaryCoolDownTime){
		FireSecondaryCastingState = ESkillCastingState::READY;
		return -2;
	}else{
		FireSecondaryCastingState = ESkillCastingState::ON_COOLDOWN;
		return (int32)(FireSecondaryCoolDownTime - TimeLeft) + 1; // +1 for displaying to player.
	}
	
}

ESkillCastingState UCharacterSkillCaster::GetFireSecondarySkillState(){
	return FireSecondaryCastingState;
}
