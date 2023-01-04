// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryComponent.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

UVictoryComponent::UVictoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

     this->OnComponentBeginOverlap.AddDynamic(this, &UVictoryComponent::OnOverlapBegin); 
}

void UVictoryComponent::BeginPlay()
{
	Super::BeginPlay();
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

void UVictoryComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Victory"));
    CheckAndTrigger();
}