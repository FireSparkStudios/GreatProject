// Copyright Epic Games, Inc. All Rights Reserved.

#include "GreatProjectGameMode.h"
#include "GreatProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGreatProjectGameMode::AGreatProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
