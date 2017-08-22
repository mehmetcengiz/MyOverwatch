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

void UCharacterSkillCaster::AbilityEPressed(){

	if(!bIsAbilityEHaveCoolDown || FPlatformTime::Seconds() - LastTimeAbilityECasted > AbilityECoolDownTime){
		UE_LOG(LogTemp, Warning, TEXT("Ability E casted."));
		LastTimeAbilityECasted = FPlatformTime::Seconds();
		OnAbilityEPressed.Broadcast();
	}else{
		float cooldown = AbilityECoolDownTime + LastTimeAbilityECasted - FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Ability E is on cooldown %f"), cooldown);
	}
}

void UCharacterSkillCaster::AbilityEReleased() {
	OnAbilityEReleased.Broadcast();
}

void UCharacterSkillCaster::AbilityShiftPressed(){

	if(!bIsAbilityShiftHaveCoolDown || FPlatformTime::Seconds()- LastTimeAbilityShiftCasted > AbilityShiftCoolDownTime){
		UE_LOG(LogTemp, Warning, TEXT("Ability Shift"));
		OnAbilityShiftPressed.Broadcast();
		LastTimeAbilityShiftCasted = FPlatformTime::Seconds();
	}else{
		float cooldown = AbilityShiftCoolDownTime + LastTimeAbilityShiftCasted - FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Ability Shift is on cooldown %f"), cooldown);
	}

}

void UCharacterSkillCaster::AbilityShiftReleased() {
	OnAbilityShiftReleased.Broadcast();
}

void UCharacterSkillCaster::AbilityJumpPressed(){
	OnAbilityJumpPressed.Broadcast();
}

void UCharacterSkillCaster::AbilityJumpReleased() {
	OnAbilityJumpReleased.Broadcast();
}

void UCharacterSkillCaster::AbilityUltimate(){

	if(CurrentUltimateCharge >= AbilityUltimateMaxCharge){
		UE_LOG(LogTemp, Warning, TEXT("Ability Ultimate"));
		OnAbilityUltimateCasted.Broadcast();
		CurrentUltimateCharge = 0;
	}
}

void UCharacterSkillCaster::ChargeUltimate(){
	CurrentUltimateCharge++;
}

int32 UCharacterSkillCaster::GetFireSecondaryCoolDown(){
	if (FireSecondaryCastingState == ESkillCastingState::HAS_NO_COOLDOWN) { return -1; } // If has no cooldown return -1

	float TimeLeft = FPlatformTime::Seconds() - LastTimeFireSecondaryCasted;
	
	if(TimeLeft > FireSecondaryCoolDownTime){
		FireSecondaryCastingState = ESkillCastingState::READY;
		return 0;
	}else{
		FireSecondaryCastingState = ESkillCastingState::ON_COOLDOWN;
		return (int32)(FireSecondaryCoolDownTime - TimeLeft) + 1; // +1 for displaying to player.
	}
	
}

ESkillCastingState UCharacterSkillCaster::GetFireSecondarySkillState(){
	return FireSecondaryCastingState;
}

int32 UCharacterSkillCaster::GetAbilityECoolDown(){
	if (AbilityECastingState == ESkillCastingState::HAS_NO_COOLDOWN) { return -1; } // If has no cooldown return -1

	float TimeLeft = FPlatformTime::Seconds() - LastTimeAbilityECasted;

	if (TimeLeft > AbilityECoolDownTime) {
		AbilityECastingState = ESkillCastingState::READY;
		return 0;
	}
	else {
		AbilityECastingState = ESkillCastingState::ON_COOLDOWN;
		return (int32)(AbilityECoolDownTime - TimeLeft) + 1; // +1 for displaying to player.
	}
}

ESkillCastingState UCharacterSkillCaster::GetAbilityESkillState(){
	return AbilityECastingState;
}

int32 UCharacterSkillCaster::GetAbilityShiftCoolDown() {
	if (AbilityShiftCastingState == ESkillCastingState::HAS_NO_COOLDOWN) { return -1; } // If has no cooldown return -1

	float TimeLeft = FPlatformTime::Seconds() - LastTimeAbilityShiftCasted;

	if (TimeLeft > AbilityShiftCoolDownTime) {
		AbilityShiftCastingState = ESkillCastingState::READY;
		return 0;
	}
	else {
		AbilityShiftCastingState = ESkillCastingState::ON_COOLDOWN;
		return (int32)(AbilityShiftCoolDownTime - TimeLeft) + 1; // +1 for displaying to player.
	}
}

ESkillCastingState UCharacterSkillCaster::GetAbilityShiftSkillState() {
	return AbilityShiftCastingState;
}

int32 UCharacterSkillCaster::GetCurrentUltimateCharge(){
	return CurrentUltimateCharge;
}

int32 UCharacterSkillCaster::GetMaxUltimateCharge(){
	return AbilityUltimateMaxCharge;
}


