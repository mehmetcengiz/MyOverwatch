// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Soldier76SecondaryProjectile.generated.h"


UCLASS()
class MYOVERWATCH_API ASoldier76SecondaryProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldier76SecondaryProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	void LaunchProjectile(float speed);

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UProjectileMovementComponent *ProjectileMovement = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category= "Components")
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 100.f;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor* OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
