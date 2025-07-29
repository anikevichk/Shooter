// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "KillAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AKillAllGameMode : public AShooterGameModeBase
{
	GENERATED_BODY()
public:
	void PawnKilled(APawn* PawnKilled) override;
};
