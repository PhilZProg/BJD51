// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryComponent.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

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
                    // APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(Actor);
                    // PlayerChar->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                    APawn* Player = Cast<APawn>(Actor);
                    AController* PlayerController = Player->GetController();
                    PlayerController->GameHasEnded(Player, true);
                    this->DestroyComponent();
                }
        }
}