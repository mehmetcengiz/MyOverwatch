// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Soldier76PrimaryProjectile.generated.h"

UCLASS()
class MYOVERWATCH_API ASoldier76PrimaryProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldier76PrimaryProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);

	UProjectileMovementComponent *projectileMovement = nullptr;
	
};
