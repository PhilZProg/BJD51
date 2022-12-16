// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerOffTrigger.h"
#include "PlayerCharacter.h"

UPowerOffTrigger::UPowerOffTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPowerOffTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void UPowerOffTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckAndTrigger();
}


void UPowerOffTrigger::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                    //TODO:
                    //Get particle system component and destroy it after character steps in trigger box and presses interaction button
                    //Also change green power light to a red light signaling that power is of
                }
        }
}