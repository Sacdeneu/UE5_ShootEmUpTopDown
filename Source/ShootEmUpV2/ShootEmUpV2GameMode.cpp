// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootEmUpV2GameMode.h"
#include "ShootEmUpV2PlayerController.h"
#include "ShootEmUpV2Character.h"
#include "UObject/ConstructorHelpers.h"

AShootEmUpV2GameMode::AShootEmUpV2GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AShootEmUpV2PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter_2"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}