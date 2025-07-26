// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Kismet\GameplayStatics.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

    if (AIBehavior == nullptr) return; 

    RunBehaviorTree(AIBehavior);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
