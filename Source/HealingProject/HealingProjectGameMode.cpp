// Copyright Epic Games, Inc. All Rights Reserved.

#include "HealingProjectGameMode.h"
#include "HealingProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHealingProjectGameMode::AHealingProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/bp_HealingProjectCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
