// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include"Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

    HUDScreen = CreateWidget(this, HUDSreenClass);
    if (HUDScreen != nullptr) HUDScreen->AddToViewport();
	
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUDScreen->RemoveFromViewport();

    if (bIsWinner){
        UUserWidget* WinScreen = CreateWidget(this, WinSreenClass);
        if (WinScreen != nullptr) WinScreen->AddToViewport();
    }
    else{
        UUserWidget* LoseScreen = CreateWidget(this, LoseSreenClass);
        if (LoseScreen != nullptr) LoseScreen->AddToViewport();
    }
    GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, RestartTime);
}