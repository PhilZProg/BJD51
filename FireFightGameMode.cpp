// Fill out your copyright notice in the Description page of Project Settings.


#include "FireFightGameMode.h"
#include "GameFramework/Controller.h"
#include "EngineUtils.h"
#include "PlayerCharacter.h"


void AFireFightGameMode::PawnKilled(APawn* PawnKilled)
{
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
        {
            EndGame(false);
        }
    
    EndGame(true);
}

void AFireFightGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
        {
            bool bIsWinner{};
            APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());

            if (Player->bDead == true)
                {
                    bIsWinner = false;
                }
            else
                {
                    bIsWinner = true;
                }
            
            Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
        }
}