// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterSkills.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYOVERWATCH_API UCharacterSkills : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterSkills();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	virtual void FirePrimary();
	virtual void FireSecondary();
	virtual void AbilityE();
	virtual void AbilityUltimate();
	virtual void AbilityJump();
		
	
};
