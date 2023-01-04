// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveTrigger.h"
#include "GameFramework/Actor.h"

UMoveTrigger::UMoveTrigger()
{
	PrimaryComponentTick.bCanEverTick = false;

    this->OnComponentBeginOverlap.AddDynamic(this, &UMoveTrigger::OnOverlapBegin); 
	this->OnComponentEndOverlap.AddDynamic(this, &UMoveTrigger::OnOverlapEnd); 
}

void UMoveTrigger::BeginPlay()
{
	Super::BeginPlay();
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

void UMoveTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AActor* Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
    Mover->SetShouldMove(true);
    UE_LOG(LogTemp, Warning, TEXT("Moving"));
    }

}

void UMoveTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Mover->SetShouldMove(false);
    UE_LOG(LogTemp, Warning, TEXT("Not moving"));
}