// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUPV2_API UWeaponItem : public UItem
{
	GENERATED_BODY()

public:

		//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		//TSubclassOf<class AWeaponActor> WeaponActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		float Accuracy;

protected:
	virtual void Use(class AShootEmUpV2Character* Character) override;

private:
	FTimerHandle TimerHandle_TimeBetweenShots;
	float LastFireTime;

		float TimeBetweenShots;
	float NextBulletSpread;
	float InitialBulletSpread;

	float GetBulletSpread() const;

public:
	virtual void Equip(class AShootEmUpV2Character* Character);
	virtual void UnEquip(class AShootEmUpV2Character* Character);

	//void StartFire(class AShootEmUpV2Character* Character);
	//void StopFire(class AShootEmUpV2Character* Character);

	UWeaponItem();

private:

		//virtual void SetOwningPawn(AShootEmUpV2Character* NewOwner);

	//AShootEmUpV2Character* MyPawn;
};
