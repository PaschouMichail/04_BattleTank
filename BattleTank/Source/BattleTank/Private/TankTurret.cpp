// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Turn(float RelativeSpeed)
{
	float TurnSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto TurnChange = TurnSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewTurn = RelativeRotation.Yaw + TurnChange;

	SetRelativeRotation(FRotator(0, RawNewTurn, 0));
}

