// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Kismet\GameplayStatics.h"
#include "PlayerCharacter.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (LineOfSightTo(PlayerPawn) && !Cast<APlayerCharacter>(GetPawn())->IsDead()){
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, Radius);
    }
    else{
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }

}
