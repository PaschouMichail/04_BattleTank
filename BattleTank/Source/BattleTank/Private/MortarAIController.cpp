// Copyright Michail Paschou

#include "MortarAIController.h"
#include "Public/TankAimingComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Public/Mortar.h"
#include "Engine/World.h"

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledMortar = GetPawn();

	if (!ensure(PlayerTank && ControlledMortar)) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius);

	UTankAimingComponent* AimingComponent = ControlledMortar->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}


void AMortarAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		AMortar* PossessedMortar = Cast<AMortar>(InPawn);
		if (!ensure(PossessedMortar)) { return; }

		PossessedMortar->OnDeath.AddUniqueDynamic(this, &AMortarAIController::OnMortarDeath);
	}
}

void AMortarAIController::OnMortarDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Mortar died."));
	if (!ensure(GetPawn())) { return; }

	GetPawn()->FindComponentByClass<UParticleSystemComponent>()->Activate();

	GetPawn()->DetachFromControllerPendingDestroy();
}
