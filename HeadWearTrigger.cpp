// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadWearTrigger.h"
#include "PlayerCharacter.h"
#include "Wearable.h"

UHeadWearTrigger::UHeadWearTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeadWearTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void UHeadWearTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckAndTrigger();
}


void UHeadWearTrigger::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                    if (HeadWeardClass)
                        {
                            APlayerCharacter* OurCharacter = Cast<APlayerCharacter>(Actor);
                            HeadWeard = GetWorld()->SpawnActor<AWearable>(HeadWeardClass);
                            HeadWeard->AttachToComponent(OurCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,TEXT("Mask"));
                            HeadWeard->SetOwner(OurCharacter);
                            OurCharacter->bWearingCloth = true;
                        }
                    GetOwner()->Destroy();
                }
        }
}