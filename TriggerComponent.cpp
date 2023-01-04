// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "PlayerCharacter.h"
#include "Tool.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

     this->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
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

void UTriggerComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor->ActorHasTag(AcceptableActorTag))
        {  
            APlayerCharacter* OurCharacter = Cast<APlayerCharacter>(OtherActor);
            if(!OurCharacter->bHasTool)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Tool handled"));
                    CheckAndTrigger();
                }
        }
}
