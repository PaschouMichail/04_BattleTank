// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "GameFramework/Controller.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius);
	
	ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());

	ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
}
