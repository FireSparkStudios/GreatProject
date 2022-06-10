// Copyright (c) 2022 [Gorkem CEYLAN]


#include "AGreatProjectGameModeBase.h"
#include "ACharacterClassBase.h"

AAGreatProjectGameModeBase::AAGreatProjectGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GreatProject/Blueprints/Characters/BP_Fighter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

