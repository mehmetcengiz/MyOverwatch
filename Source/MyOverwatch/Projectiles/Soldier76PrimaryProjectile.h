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
	
	void LaunchProjectile(float speed);

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UProjectileMovementComponent *projectileMovement = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category= "Components")
	UStaticMeshComponent *collisionMesh = nullptr;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
