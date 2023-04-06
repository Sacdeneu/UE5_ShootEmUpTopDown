// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "ShootEmUpV2/ShootEmUpV2Character.h"

void UWeaponItem::Use(AShootEmUpV2Character* Character)
{
	Equip(Character);
}

void UWeaponItem::Equip(AShootEmUpV2Character* Character)
{
	if (Character)
	{
		/*if (Character->bIsWeaponEquipped)
		{
			UnEquip(Character);
		}

			MyPawn = Character;

		if (WeaponActorClass)
		{
			AWeaponActor* NewWeapon = Character->GetWorld()->SpawnActor<AWeaponActor>(WeaponActorClass);
			if (NewWeapon)
			{
				NewWeapon->SetOwningCharacter(Character);
				Character->SetEquippedWeapon(NewWeapon);

				NextBulletSpread = InitialBulletSpread = NewWeapon->GetBulletSpread();
			}
		}*/

		//bIsWeaponEquipped = true;
	}

}

void UWeaponItem::UnEquip(AShootEmUpV2Character* Character)
{
	if (Character)
	{
		/*if (Character->GetEquippedWeapon())
		{
			Character->GetEquippedWeapon()->Destroy();
			Character->SetEquippedWeapon(nullptr);
			Character->bIsWeaponEquipped = false;
		}*/
	}
}

float UWeaponItem::GetBulletSpread() const
{
	float FinalBulletSpread = FMath::Min(NextBulletSpread, Accuracy);
	//NextBulletSpread += InitialBulletSpread / 2.f;
	return FinalBulletSpread;
}

UWeaponItem::UWeaponItem()
{
	Weight = 5.f;
	ItemDisplayName = FText::FromString("Weapon");
	UseActionText = FText::FromString("Equip");
	Damage = 10.f;
	FireRate = 0.1f;
	Accuracy = 0.9f;
}
