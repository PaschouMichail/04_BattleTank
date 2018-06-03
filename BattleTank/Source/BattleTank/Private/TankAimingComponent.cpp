// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Public/Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Set Starting Ammo
	Ammo = 12;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//initial Firing State must be reloaded
	LastFireTime = FPlatformTime::Seconds();
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo == 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)	//FPlatformTime::Seconds()
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

int32 UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam);

	//Calculate the OutLaunchVelocity
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

	if (FiringState != EFiringState::Reloading && Ammo != 0)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Tip")), Barrel->GetSocketRotation(FName("Tip")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		Ammo = Ammo - 1;
	}
}

void UTankAimingComponent::MoveBarrel(FVector TargetAimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = TargetAimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	float TurretYaw = Turret->GetForwardVector().Rotation().Yaw;
	float AimsAsYaw = AimDirection.Rotation().Yaw;
	float DeltaYaw = 0.f;

	if (AimsAsYaw > 0 && TurretYaw < 0)
	{
		float a = -TurretYaw + AimsAsYaw;
		float b = 180 + TurretYaw + 180 - AimsAsYaw;

		if (a < b)
		{
			DeltaYaw = a;
		}
		else
		{
			DeltaYaw = -b;
		}
	}
	else if (AimsAsYaw < 0 && TurretYaw>0)
	{
		float a = -AimsAsYaw + TurretYaw;
		float b = 180 + AimsAsYaw + 180 - TurretYaw;

		if (a < b)
		{
			DeltaYaw = -a;
		}
		else
		{
			DeltaYaw = b;
		}
	}
	else
	{
		DeltaYaw = AimsAsYaw - TurretYaw;
	}

	Turret->Turn(DeltaYaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.05);
}