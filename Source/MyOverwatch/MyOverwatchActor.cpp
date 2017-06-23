// This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "MyOverwatchActor.h"


// Sets default values
AMyOverwatchActor::AMyOverwatchActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyOverwatchActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyOverwatchActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyOverwatchActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	
	UE_LOG(LogTemp, Warning, TEXT("%s got damage!! "), *GetName());

	return Damage;

}

