// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyOverwatch.h"
#include "MyOverwatchCharacter.h"
#include "MyOverwatchProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "MotionControllerComponent.h"
#include "Components/CharacterHealthComponent.h"
#include "CharacterSkillCaster.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AMyOverwatchCharacter

AMyOverwatchCharacter::AMyOverwatchCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	//Character Skill Caster
	CharacterSkillCaster = CreateDefaultSubobject<UCharacterSkillCaster>(TEXT("CharacterSkillCaster"));
	//Character Health
	CharacterHealthComponent = CreateDefaultSubobject<UCharacterHealthComponent>(TEXT("CharacterHealth"));


}

void AMyOverwatchCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		Mesh1P->SetHiddenInGame(false, true);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyOverwatchCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyOverwatchCharacter::AbilityJumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyOverwatchCharacter::AbilityJumpReleased);

	PlayerInputComponent->BindAction("AbilityE", IE_Pressed, this, &AMyOverwatchCharacter::AbilityEPressed);
	PlayerInputComponent->BindAction("AbilityQ", IE_Pressed, this, &AMyOverwatchCharacter::AbilityUltimate);
	PlayerInputComponent->BindAction("FirePrimary", IE_Pressed, this, &AMyOverwatchCharacter::FirePrimaryPressed);
	PlayerInputComponent->BindAction("FirePrimary", IE_Released, this, &AMyOverwatchCharacter::FirePrimaryReleased);
	PlayerInputComponent->BindAction("FireSecondary", IE_Pressed, this, &AMyOverwatchCharacter::FireSecondaryPressed);
	PlayerInputComponent->BindAction("FireSecondary", IE_Released, this, &AMyOverwatchCharacter::FireSecondaryReleased);
	PlayerInputComponent->BindAction("AbilityUltimate", IE_Pressed, this, &AMyOverwatchCharacter::AbilityUltimate);
	PlayerInputComponent->BindAction("AbilityShift", IE_Pressed, this, &AMyOverwatchCharacter::AbilityShiftPressed);
	PlayerInputComponent->BindAction("AbilityShift", IE_Released, this, &AMyOverwatchCharacter::AbilityShiftReleased);
	
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyOverwatchCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyOverwatchCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyOverwatchCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyOverwatchCharacter::LookUpAtRate);
}

void AMyOverwatchCharacter::AbilityEPressed(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityEPressed();
}

void AMyOverwatchCharacter::AbilityEReleased(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityEReleased();
}

void AMyOverwatchCharacter::AbilityShiftPressed(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityShiftPressed();

}

void AMyOverwatchCharacter::AbilityShiftReleased(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityShiftReleased();
}

void AMyOverwatchCharacter::AbilityUltimate(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityUltimate();
	
}

void AMyOverwatchCharacter::AbilityJumpPressed(){
	ACharacter::Jump();
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityJumpPressed();
}

void AMyOverwatchCharacter::AbilityJumpReleased(){
	ACharacter::StopJumping();
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->AbilityJumpReleased();

}

void AMyOverwatchCharacter::FirePrimaryPressed()
{
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->FirePrimaryPressed();
	// try and fire a projectile
	//if (ProjectileClass != NULL) {
	//
	//	UWorld* const World = GetWorld();
	//
		//if (World != NULL) {
			//const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
//			FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//
	//		// spawn the projectile at the muzzle
		//	World->SpawnActor<AMyOverwatchProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		//}
	//}
}

void AMyOverwatchCharacter::FirePrimaryReleased(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->FirePrimaryReleased();
}

void AMyOverwatchCharacter::FireSecondaryPressed(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->FireSecondaryPressed();
}


void AMyOverwatchCharacter::FireSecondaryReleased(){
	if (CharacterSkillCaster == nullptr) { return; }
	CharacterSkillCaster->FireSecondaryReleased();
}

void AMyOverwatchCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyOverwatchCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyOverwatchCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyOverwatchCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AMyOverwatchCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyOverwatchCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AMyOverwatchCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyOverwatchCharacter::TouchUpdate);
	}
	return bResult;
}

void AMyOverwatchCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location) {
	if (TouchItem.bIsPressed == true) {
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AMyOverwatchCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location) {
	if (TouchItem.bIsPressed == false){
		return;
	}

	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false)){
		FirePrimaryPressed();
	}

	TouchItem.bIsPressed = false;
}

float AMyOverwatchCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	if (CharacterHealthComponent) {
		CharacterHealthComponent->TakeDamage(Damage);
	}
	return Damage;
}

UCharacterSkillCaster* AMyOverwatchCharacter::GetCharacterSkillCasterComponent(){
	return CharacterSkillCaster;
}

UCharacterHealthComponent* AMyOverwatchCharacter::GetCharacterHealthComponent() {
	return CharacterHealthComponent;
}
