// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "MyOverwatchGameMode.generated.h"

UCLASS(minimalapi)
class AMyOverwatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AMyOverwatchGameMode();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
};



