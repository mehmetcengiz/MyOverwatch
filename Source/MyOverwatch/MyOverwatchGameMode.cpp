// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyOverwatch.h"
#include "MyOverwatchGameMode.h"
#include "MyOverwatchHUD.h"
#include "MyOverwatchCharacter.h"
#include "Blueprint/UserWidget.h"


void AMyOverwatchGameMode::BeginPlay(){
	Super::BeginPlay();
	
	AMyOverwatchCharacter* MyCharacter = Cast<AMyOverwatchCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if(PlayerHUDClass != NULL){
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if(CurrentWidget != NULL){
			CurrentWidget->AddToViewport();
		}
	}

	
}

AMyOverwatchGameMode::AMyOverwatchGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Characters/Blueprints/Soldier76/BP_Soldier76"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMyOverwatchHUD::StaticClass();
}
