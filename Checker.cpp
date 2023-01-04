// Fill out your copyright notice in the Description page of Project Settings.


#include "Checker.h"
#include "PlayerCharacter.h"

UChecker::UChecker()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UChecker::BeginPlay()
{
	Super::BeginPlay();
}

AActor* UChecker::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                    return Actor;
                }
        }
    return nullptr;
}  