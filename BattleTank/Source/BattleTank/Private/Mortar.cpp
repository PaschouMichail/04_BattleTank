// Copyright Michail Paschou

#include "Mortar.h"


// Sets default values
AMortar::AMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMortar::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = StartingHealth;
}

// Called to bind functionality to input
void AMortar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMortar::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float AMortar::GetHealthPercent() const
{
	return  (float)CurrentHealth / (float)StartingHealth;
}
