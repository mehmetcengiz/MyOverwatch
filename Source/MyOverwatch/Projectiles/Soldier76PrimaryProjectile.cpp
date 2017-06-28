// Fill out your copyright notice in the Description page of Project Settings.

#include "MyOverwatch.h"
#include "Soldier76PrimaryProjectile.h"


// Sets default values
ASoldier76PrimaryProjectile::ASoldier76PrimaryProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	projectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ASoldier76PrimaryProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic(this, &ASoldier76PrimaryProjectile::OnHit);
}

void ASoldier76PrimaryProjectile::LaunchProjectile(float speed) {
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

void ASoldier76PrimaryProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
	Destroy();
}
