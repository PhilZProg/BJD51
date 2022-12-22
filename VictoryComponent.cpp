// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryComponent.h"

UVictoryComponent::UVictoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVictoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UVictoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckAndTrigger();
}


void UVictoryComponent::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                  APawn* Player = Cast<APawn>(Actor);
                  AController* PlayerController = Player->GetController();
                  PlayerController->GameHasEnded(Player, true);
                }
        }
}