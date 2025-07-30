// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllGameMode.h"

void AKillAllGameMode::PawnKilled(APawn* PawnKilled){
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if (PlayerController != nullptr){
        PlayerController->GameHasEnded(nullptr, false);
    }
}