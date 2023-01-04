// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadWearTrigger.h"
#include "PlayerCharacter.h"
#include "Wearable.h"

UHeadWearTrigger::UHeadWearTrigger()
{
	PrimaryComponentTick.bCanEverTick = false;

    this->OnComponentBeginOverlap.AddDynamic(this, &UHeadWearTrigger::OnOverlapBegin); 
}

void UHeadWearTrigger::BeginPlay()
{
	Super::BeginPlay();
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

void UHeadWearTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckAndTrigger();
    UE_LOG(LogTemp, Warning, TEXT("Cloth worn"));
}