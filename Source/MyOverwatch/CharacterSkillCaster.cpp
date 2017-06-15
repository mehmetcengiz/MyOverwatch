// Fill out your copyright notice in the Description page of Project Settings.

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

	// ...
	
}

void UCharacterSkillCaster::PimaryFire(){
	UE_LOG(LogTemp, Warning, TEXT("Character primary shoot!"));


}

void UCharacterSkillCaster::SecondaryFire(){
}

void UCharacterSkillCaster::AbilityE(){
}

void UCharacterSkillCaster::AbilityShift(){
}

void UCharacterSkillCaster::AbilityJump(){
}



