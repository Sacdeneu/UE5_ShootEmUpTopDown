// Fill out your copyright notice in the Description page of Project Settings.

#include "Crate.h"
#include "UObject/UObjectGlobals.h"
#include "InventoryComponent.h"
#include "ShootEmUpV2/ShootEmUpV2Character.h"
#include "UObject/UObjectGlobals.h"


ACrate::ACrate()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
    bIsOpened = false;
    // Create the crate mesh
    CrateBottomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrateBottomMesh"));
    // Create the crate mesh
    CrateTopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrateTopMesh"));
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    CrateBottomMesh->SetupAttachment(RootComponent);
    CrateTopMesh->SetupAttachment(RootComponent);

    // Set up default loot table
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CrateBottomMeshAsset(TEXT("/Game/Assets/Textures/Crate/Sci-fi_Military_Container_Bottom.Sci-fi_Military_Container_Bottom"));
    if (CrateBottomMeshAsset.Succeeded())
    {
        CrateBottomMesh->SetStaticMesh(CrateBottomMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CrateTopMeshAsset(TEXT("/Game/Assets/Textures/Crate/Sci-fi_Military_Container_Top.Sci-fi_Military_Container_Top"));
    if (CrateTopMeshAsset.Succeeded())
    {
        CrateTopMesh->SetStaticMesh(CrateTopMeshAsset.Object);
    }
}

void ACrate::OnCanInteract(AShootEmUpV2Character* PlayerCharacter)
{
}

void ACrate::OnInteract(AShootEmUpV2Character* PlayerCharacter)
{
    /*if (PlayerCharacter)
    {
        GenerateLoot(PlayerCharacter);

        // Optionally, add visual feedback for opening the crate

        // Destroy the crate after looting
        Destroy();
    }*/
}


void ACrate::Interact_Implementation()
{

}

void ACrate::CanInteract_Implementation()
{

}


void ACrate::GenerateLoot(AShootEmUpV2Character* PlayerCharacter)
{
    if (LootTable.Num() > 0)
    {
        // Randomly select an item from the loot table
        TSubclassOf<UItem> SelectedItem = LootTable[FMath::RandRange(0, LootTable.Num() - 1)];

        if (PlayerCharacter && SelectedItem)
        {
            // Add the item to the player's inventory
            UItem* NewItem = NewObject<UItem>(PlayerCharacter, SelectedItem);
            if (NewItem)
            {
                PlayerCharacter->GetInventory()->AddItem(NewItem);
            }
        }
    }
}