// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InventorySystem/Items/WeaponItem.h"
#include "ShootEmUpV2Character.generated.h"

UCLASS(config=Game)
class AShootEmUpV2Character : public ACharacter
{
	GENERATED_BODY()

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* Inventory;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		float Score;
	/* Weapon Equipped */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		bool bIsWeaponEquipped;

	/* Weapon Item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		UWeaponItem* EquippedWeapon;
public:
	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UItem* Item);
	/* Use Weapon */
	//UFUNCTION(BlueprintCallable, Category = "Inventory")
		//void UseWeapon(UWeaponItem* Weapon);

public:
	AShootEmUpV2Character();
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

