// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "PlayerCharacter.h"
#include "Tool.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckAndTrigger();
}


void UTriggerComponent::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                    if (ToolClass)
                        {
                            APlayerCharacter* OurCharacter = Cast<APlayerCharacter>(Actor);
                            Tool = GetWorld()->SpawnActor<ATool>(ToolClass);
                            Tool->AttachToComponent(OurCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
                            Tool->SetOwner(OurCharacter);
                            OurCharacter->bHasTool = true;
                        }
                    GetOwner()->Destroy();
                }
        }
}