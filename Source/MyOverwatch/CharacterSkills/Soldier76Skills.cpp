// Fill out your copyright notice in the Description page of Project Settings.

#include "MyOverwatch.h"
#include "Soldier76Skills.h"


// Sets default values for this component's properties
USoldier76Skills::USoldier76Skills()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USoldier76Skills::BeginPlay()
{
	Super::BeginPlay();
	//TODO Bind the events of player skills.
	
}


// Called every frame
void USoldier76Skills::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USoldier76Skills::FireSecondary(){
	UE_LOG(LogTemp, Warning, TEXT("Fire By Soldier76"));
}

