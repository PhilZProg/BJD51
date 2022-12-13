// Copyright Epic Games, Inc. All Rights Reserved.

#include "BJD51GameMode.h"
#include "BJD51Character.h"
#include "UObject/ConstructorHelpers.h"

ABJD51GameMode::ABJD51GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
