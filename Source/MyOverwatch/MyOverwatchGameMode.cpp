// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyOverwatch.h"
#include "MyOverwatchGameMode.h"
#include "MyOverwatchHUD.h"
#include "MyOverwatchCharacter.h"

AMyOverwatchGameMode::AMyOverwatchGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Characters/Soldier76"));//FirstPersonCPP/Blueprints/FirstPersonCharacter
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMyOverwatchHUD::StaticClass();
}
