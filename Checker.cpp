// Fill out your copyright notice in the Description page of Project Settings.


#include "Checker.h"
#include "PlayerCharacter.h"

UChecker::UChecker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UChecker::BeginPlay()
{
	Super::BeginPlay();
}

void UChecker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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