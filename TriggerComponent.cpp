// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "GameFramework/Actor.h"
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

    GetAcceptableActor();

    //AActor* Actor = GetAcceptableActor();
    // if (Actor != nullptr)
    //     {
    //         UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
    //         if (Component != nullptr)
    //             {   
    //                 Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
    //                 Component->SetSimulatePhysics(false);
    //             }
    //         Mover->SetShouldMove(true);
    //     }
    // else
    //     {
    //         Mover->SetShouldMove(false);
    //     }
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

void UTriggerComponent::GetAcceptableActor()
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
                        }
                    GetOwner()->Destroy();
                }
        }
}