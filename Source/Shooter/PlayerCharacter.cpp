// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameModeBase.h"
#include "HealthPotion.h"
#include "EngineUtils.h"  

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		if (Gun)
		{
			GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			Gun->SetOwner(this);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Gun could not be spawned."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GunClass is not set on %s"), *GetName());
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float ClosestDistance = FLT_MAX;
    NearbyHealthPickup = nullptr;

    for (TActorIterator<AHealthPotion> It(GetWorld()); It; ++It)
    {
        AHealthPotion* Potion = *It;
        float Dist = FVector::Dist(Potion->GetActorLocation(), GetActorLocation());
        if (Dist <= Potion->PickupDistance && Dist < ClosestDistance)
        {
            ClosestDistance = Dist;
            NearbyHealthPickup = Potion;
        }
    }
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Shoot()
{
    if (Gun){
        Gun->PullTrigger();
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("Gun is null"));
    }
}


float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser){
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Current health: %f"), CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), DamageToApply);

	if (IsDead()){

		AShooterGameModeBase* GameMode =GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
		if (GameMode!=nullptr) GameMode->PawnKilled(this);

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}


	return DamageToApply;
}

bool APlayerCharacter::IsDead() const {
	return CurrentHealth <= 0;
}

float APlayerCharacter::GetHealthPercent() const
{
    return CurrentHealth/MaxHealth;
}

void APlayerCharacter::PickUp()
{
	if (NearbyHealthPickup){
        NearbyHealthPickup->Pickup();
		UE_LOG(LogTemp, Warning, TEXT("Trying to pickup"));
    }
}

void APlayerCharacter::AddHealth(float Amount)
{
    CurrentHealth += Amount;
	if (CurrentHealth > MaxHealth)
    {
        CurrentHealth = MaxHealth;  
    }
}
