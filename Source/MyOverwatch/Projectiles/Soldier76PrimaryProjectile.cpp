// Fill out your copyright notice in the Description page of Project Settings.

#include "MyOverwatch.h"
#include "Soldier76PrimaryProjectile.h"


// Sets default values
ASoldier76PrimaryProjectile::ASoldier76PrimaryProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoldier76PrimaryProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoldier76PrimaryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

