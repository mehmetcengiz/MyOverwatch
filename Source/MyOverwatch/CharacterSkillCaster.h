// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterSkillCaster.generated.h"

class UCharacterSkills;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API UCharacterSkillCaster : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterSkillCaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void FirePrimary();
	void FireSecondary();
	void AbilityE();
	void AbilityShift();
	void AbilityJump();
	void AbilityUltimate();



};
