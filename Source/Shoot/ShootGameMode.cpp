// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootGameMode.h"
#include "ShootCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootGameMode::AShootGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
