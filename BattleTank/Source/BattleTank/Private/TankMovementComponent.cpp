// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftFrontTrackToSet, UTankTrack* RightFrontTrackToSet, UTankTrack* LeftBackTrackToSet, UTankTrack* RightBackTrackToSet)
{	
	LeftFrontTrack = LeftFrontTrackToSet;
	LeftBackTrack = LeftBackTrackToSet;
	RightFrontTrack = RightFrontTrackToSet;
	RightBackTrack = RightBackTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%s MoveVelocity: %s"), *GetOwner()->GetName(), *MoveVelocity.GetSafeNormal().ToString())
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftBackTrack) || !ensure(RightBackTrack) || !ensure(RightFrontTrack) || !ensure(LeftFrontTrack)) { return; }
	LeftFrontTrack->SetThrottle(Throw);
	LeftBackTrack->SetThrottle(Throw);
	RightFrontTrack->SetThrottle(Throw);
	RightBackTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftBackTrack) || !ensure(RightBackTrack) || !ensure(RightFrontTrack) || !ensure(LeftFrontTrack)) { return; }
	LeftFrontTrack->SetThrottle(Throw);
	LeftBackTrack->SetThrottle(Throw);
	RightFrontTrack->SetThrottle(-Throw);
	RightBackTrack->SetThrottle(-Throw);
}