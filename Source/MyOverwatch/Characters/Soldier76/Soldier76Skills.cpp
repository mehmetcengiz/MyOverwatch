//This is example game project by Mehmet Cengiz.Source available on github.com/mehmetcengiz/MyOverwatch 

#include "MyOverwatch.h"
#include "Soldier76Skills.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h" //TODO delete later it is for screen debuging.
#include "./Characters/Soldier76/Soldier76SecondaryProjectile.h"
#include "./Characters/Soldier76/Soldier76Healer.h"
#include "Soldier76Ultimate.h"
#include "./Components/ShootingComponent.h"

#define OUT

// Sets default values for this component's properties
USoldier76Skills::USoldier76Skills(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USoldier76Skills::BeginPlay() {
	Super::BeginPlay();
	//TODO Bind the events of player skills.
	//ShootingComponent = GetOwner()->FindComponentByClass<UShootingComponent>();
}


// Called every frame
void USoldier76Skills::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Soldier76 keeps shooting when player keep pressing button.
void USoldier76Skills::FirePrimaryPressed(){
	if (ShootingComponent == NULL) { return; }
	ShootingComponent->SetPlayerIsShooting(true);
}

//Soldier76 stops shooting when player released button.
void USoldier76Skills::FirePrimaryReleased(){
	if (ShootingComponent == NULL) { return; }
	ShootingComponent->SetPlayerIsShooting(false);

}

void USoldier76Skills::FireSecondary(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary fireSecondary casted by Soldier76");

	if (FirstPersonCamera == NULL) { return; }

	auto Location = FirstPersonCamera->GetComponentLocation();
	auto ForwardVector = FirstPersonCamera->GetForwardVector();
	float Offset = 100;	//TODO tune offset after.
	Location += (ForwardVector * Offset);

	auto Rotator = FirstPersonCamera->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<ASoldier76SecondaryProjectile>(ProjectileBluePrint, Location, Rotator);
	Projectile->LaunchProjectile(SecondaryProjectileSpeed);

	//Firing sound.
	if (FireSound != NULL){
		FVector ActorLocation;
		ActorLocation = GetOwner()->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, ActorLocation);
	}

	//Play firing animation.
	if (FireAnimation != NULL){
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL){
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void USoldier76Skills::AbilityE(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary E casted by Soldier76");

	auto CharacterLocation = GetOwner()->GetActorLocation();
	FVector Location = FVector(CharacterLocation.X, CharacterLocation.Y, 170.f);	
	auto HeallerActor = GetWorld()->SpawnActor<ASoldier76Healer>(SoldierHealerBluePrint, Location, FRotator(0, 0, 0));


	

}

void USoldier76Skills::AbilityUltimate(){
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Secondary Q casted by Soldier76");
	
	if(FirstPersonCamera == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Camera component is null."));
		return;
	}

	auto Location = FirstPersonCamera->GetComponentLocation();
	auto Rotator = FirstPersonCamera->GetComponentRotation();

	auto UltimateCone = GetWorld()->SpawnActor<ASoldier76Ultimate>(Soldier76UltimateCone, Location, Rotator);
	UltimateCone->SetCameraComponent(FirstPersonCamera);
	Soldier76Ultimate = UltimateCone;
	

}

void USoldier76Skills::AbilityShiftPressed(){
	bIsShiftCasted = true;
	ChangeRunningSpeed(FastRunningSpeed);
}

void USoldier76Skills::AbilityShiftReleased(){
	bIsShiftCasted = false;
	ChangeRunningSpeed(DefaultRunningSpeed);
}

void USoldier76Skills::AbilityJump(){
}

void USoldier76Skills::SetShootingSkeletalMeshComponent(USkeletalMeshComponent* Mesh){
	Mesh1P = Mesh;
}

void USoldier76Skills::ChangeRunningSpeed(float speed){
	MovementComponent->MaxWalkSpeed = speed;
}

void USoldier76Skills::SetMovementComponent(UCharacterMovementComponent* MovementComponentToSet){
	MovementComponent = MovementComponentToSet;
}

void USoldier76Skills::SetCameraComponent(UCameraComponent* CameraToSet){
	FirstPersonCamera = CameraToSet;
}

void USoldier76Skills::SetShootingComponent(UShootingComponent* ShootingComponentToSet){
	UE_LOG(LogTemp, Warning, TEXT("Shooting component is set"));
	ShootingComponent = ShootingComponentToSet;
}


