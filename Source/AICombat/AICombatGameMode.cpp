// Copyright Epic Games, Inc. All Rights Reserved.

#include "AICombatGameMode.h"
#include "AICombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAICombatGameMode::AAICombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
