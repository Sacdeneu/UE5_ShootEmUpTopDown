#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "../../Interfaces/InteractableInterface.h"
#include "Crate.generated.h"

/**
 *
 */
UCLASS()

class SHOOTEMUPV2_API ACrate : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ACrate();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* CrateBottomMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* CrateTopMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TArray<TSubclassOf<UItem>> LootTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsOpened;

	void GenerateLoot(AShootEmUpV2Character* PlayerCharacter);

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnCanInteract(class AShootEmUpV2Character* PlayerCharacter);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnInteract(class AShootEmUpV2Character* PlayerCharacter);

	virtual void Interact_Implementation() override;
	virtual void CanInteract_Implementation() override;
};
