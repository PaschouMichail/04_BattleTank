// Copyright Michail Paschou

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortarDelegate);

UCLASS()
class BATTLETANK_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMortar();

	UPROPERTY(EditDefaultsOnly, Category = Health)
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)
		int32 CurrentHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//Returns currentHealth as a percentage of StartingHealth between 0 and 1
	UFUNCTION(BLueprintPure, Category = Health)
		float GetHealthPercent() const;

	FMortarDelegate OnDeath;
};
