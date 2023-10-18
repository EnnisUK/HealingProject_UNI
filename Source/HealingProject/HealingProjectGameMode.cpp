// Copyright Epic Games, Inc. All Rights Reserved.

#include "HealingProjectGameMode.h"
#include "HealingProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHealingProjectGameMode::AHealingProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/bp_CharHealing"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("BP not found"));
	}
}
