// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"



// Sets default values
AHealthPotion::AHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthPotion::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn =  Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

// Called every frame
void AHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f, 90.f * DeltaTime, 0.f), false, nullptr, ETeleportType::None);


}

void AHealthPotion::Pickup(){
	if (PlayerPawn){
		PlayerPawn->AddHealth(20.f);;
		Destroy();
	}
}
