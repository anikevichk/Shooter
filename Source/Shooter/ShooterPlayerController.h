// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor *EndGameFocus = nullptr, bool bIsWinner = false) override;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseSreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinSreenClass;

	UPROPERTY(EditAnywhere)
	float RestartTime  = 5;

	FTimerHandle TimerHandle;
};
