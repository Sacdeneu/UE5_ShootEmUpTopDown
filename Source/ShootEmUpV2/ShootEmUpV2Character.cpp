// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootEmUpV2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "InventorySystem/Items/Item.h"
#include "InventorySystem/Items/InventoryComponent.h"
#include <Actions/PawnAction.h>
#include "ShootEmUpV2PlayerController.h"
#include "InventorySystem/Items/Crate.h"

AShootEmUpV2Character::AShootEmUpV2Character()
{
	Health = 100.f;
	Score = 0.f;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;
	InteractionRange = 200.f;
	// Set up initial variables
	bIsWeaponEquipped = false;
	EquippedWeapon = nullptr;
}

//void AShootEmUpV2Character::EquipWeapon(UWeaponItem* NewWeapon)
//{
//	if (NewWeapon != nullptr)
//	{
//		if (EquippedWeapon != nullptr)
//		{
//			EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
//			EquippedWeapon->Destroy();
//		}
//
//		EquippedWeapon = NewWeapon;
//		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachPointName);
//		EquippedWeapon->SetOwner(this);
//		bIsWeaponEquipped = true;
//	}
//}
//
//void AShootEmUpV2Character::OnFire()
//{
//	if (bIsWeaponEquipped && EquippedWeapon != nullptr)
//	{
//		EquippedWeapon->Fire();
//	}
//}

//////////////////////////////////////////////////////////////////////////
// Input

void AShootEmUpV2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootEmUpV2Character::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AShootEmUpV2Character::Interact);

	}

}

void AShootEmUpV2Character::Interact()
{
	FVector Start = GetActorLocation();
	Start.Z -= 100.0f;
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start + ForwardVector * InteractionRange;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// Perform a trace to check for a crate
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		if (IInteractableInterface* Interactable = Cast<IInteractableInterface>(HitResult.GetActor()))
		{

			// Interact with the crate
			IInteractableInterface::Execute_Interact(HitResult.GetActor());
		}
	}
}


void AShootEmUpV2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

		FVector Start = GetActorLocation();
		Start.Z -= 100.0f;
		FVector ForwardVector = GetActorForwardVector();
		FVector End = Start + ForwardVector * InteractionRange;

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		// Perform a trace to check for a crate
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
		{
			if (IInteractableInterface* Interactable = Cast<IInteractableInterface>(HitResult.GetActor()))
			{

				// Interact with the crate
				IInteractableInterface::Execute_CanInteract(HitResult.GetActor());
			}
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.0f, 0, 2.0f);
}

UInventoryComponent* AShootEmUpV2Character::GetInventory() const
{
	return Inventory;
}

void AShootEmUpV2Character::UseItem(class UItem* Item)
{
	if (Item) {
		Item->Use(this);
		Item->OnUse(this); //bp event
	}
}

void AShootEmUpV2Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
