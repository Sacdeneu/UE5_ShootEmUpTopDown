// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTEMUPV2_API UHealthItem : public UItem
{
	GENERATED_BODY()

public:

	/**The weight of the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float HealthToHeal;

protected:
	virtual void Use(class AShootEmUpV2Character* Character) override;


};
