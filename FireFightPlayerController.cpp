// Fill out your copyright notice in the Description page of Project Settings.


#include "FireFightPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AFireFightPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromParent();

    if (bIsWinner)
        {
            UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

            if(WinScreen != nullptr)
                {
                    WinScreen->AddToViewport();
                }
        }
    else
        {
            UUserWidget* LooseScreen = CreateWidget(this, LooseScreenClass);

            if(LooseScreen != nullptr)
                {
                    LooseScreen->AddToViewport();
                }
        }

    GetWorldTimerManager().SetTimer(Timer,this, &AFireFightPlayerController::BackToMainMenu, Delay);
}

void AFireFightPlayerController::BeginPlay()
{

    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);

            if(HUD != nullptr)
                {
                    HUD->AddToViewport();
                }
}

void AFireFightPlayerController::BackToMainMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(),FName("MainMenu"));
}


