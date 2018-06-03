// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void OnTankDeath();

	virtual void SetPawn(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere)
		float CrossshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.333333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
