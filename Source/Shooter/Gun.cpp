// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components\SkeletalMeshComponent.h"
#include "Kismet\GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AController* AGun::GetOwnerController() const{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}


bool AGun::SetUpGunTrace(FHitResult& Hit, FVector& Direction){

	AController *OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	Direction = -Rotation.Vector();
	FVector End = Rotation.Vector()*MaxRange + Location;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector Direction;

	AController *OwnerController = GetOwnerController();
	bool hit = SetUpGunTrace(Hit, Direction);

	if(hit){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, Direction.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location);

		AActor* HitedActor = Hit.GetActor();

		if(HitedActor == nullptr) return;
		FPointDamageEvent DamageEvent{Damage, Hit, Direction, nullptr};
		HitedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}

}
