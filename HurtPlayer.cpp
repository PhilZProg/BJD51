// Fill out your copyright notice in the Description page of Project Settings.


#include "HurtPlayer.h"
#include "PlayerCharacter.h"
#include "Engine/DamageEvents.h"

UHurtPlayer::UHurtPlayer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHurtPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void UHurtPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckAndTrigger();
}


void UHurtPlayer::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                    FDamageEvent DamageEvent;
					AController* OwnerController = GetOwnerContorller();
                    Actor->TakeDamage(Damage, DamageEvent,OwnerController,nullptr);
                }
        }
}

AController* UHurtPlayer::GetOwnerContorller() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		{
			return nullptr;
		}
	return OwnerPawn->GetController();	
}