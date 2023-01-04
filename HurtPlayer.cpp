// Fill out your copyright notice in the Description page of Project Settings.


#include "HurtPlayer.h"
#include "PlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"



UHurtPlayer::UHurtPlayer()
{
	PrimaryComponentTick.bCanEverTick = false;

    HurtRate = 0.2f;	

	bShouldHurt = true;

	bHurting = false;

    this->OnComponentBeginOverlap.AddDynamic(this, &UHurtPlayer::OnOverlapBegin); 
	this->OnComponentEndOverlap.AddDynamic(this, &UHurtPlayer::OnOverlapEnd); 
}

void UHurtPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void UHurtPlayer::CheckAndTrigger()
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor : Actors)
        {
            if (Actor->ActorHasTag(AcceptableActorTag))
                {
                    APlayerCharacter* OurCharacter = Cast<APlayerCharacter>(Actor);
                    if (OurCharacter->bCrouch == false || OurCharacter->bWearingCloth == false)
                    {
                        FDamageEvent DamageEvent;
                        AController* OwnerController = nullptr; 
                        Actor->TakeDamage(Damage, DamageEvent,OwnerController,nullptr);
                    }
                }
        }
}

void UHurtPlayer::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Hurting();
    UE_LOG(LogTemp, Warning, TEXT("Hurting"));
}

void UHurtPlayer::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    NotHurting();
    UE_LOG(LogTemp, Warning, TEXT("Not hurting"));
}

void UHurtPlayer::Hurting()
{
		bHurting = true;
		StartAutoHurtTimer();
} 

void UHurtPlayer::NotHurting()
{
			bHurting = false;
}

void UHurtPlayer::StartAutoHurtTimer()
{
	if (bShouldHurt)
		{
            CheckAndTrigger();
			bShouldHurt = false;
			GetWorld()->GetTimerManager().SetTimer(AutoHurtTimer, this, &UHurtPlayer::AutoHurtTimerReset, HurtRate);
		}
}

void UHurtPlayer::AutoHurtTimerReset()
{
	bShouldHurt = true;
	if (bHurting)
		{
			StartAutoHurtTimer();
		}
}