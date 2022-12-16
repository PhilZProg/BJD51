// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveTrigger.h"
#include "GameFramework/Actor.h"

UMoveTrigger::UMoveTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMoveTrigger::BeginPlay()
{
	Super::BeginPlay();
}


void UMoveTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    AActor* Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

void UMoveTrigger::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor* UMoveTrigger::GetAcceptableActor() const
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