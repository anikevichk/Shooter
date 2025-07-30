// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include"Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UUserWidget* LoseScreen = CreateWidget(this, LoseSreenClass);
    if (LoseScreen != nullptr) LoseScreen->AddToViewport();
    
    GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, RestartTime);
}