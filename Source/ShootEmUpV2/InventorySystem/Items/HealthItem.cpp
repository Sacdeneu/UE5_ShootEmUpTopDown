// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthItem.h"
#include "InventoryComponent.h"
#include "ShootEmUpV2/ShootEmUpV2Character.h"

void UHealthItem::Use(AShootEmUpV2Character* Character)
{
	if (Character) {
		Character->Health += HealthToHeal;

		if (OwningInventory) {
			OwningInventory->RemoveItem(this);
		}
	}
}
