// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ATank;
/**
 * TankTrack is used to set maximum driving force and apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BLueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	//Max Force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float TrackMaxDrivingForce = 600000;	//Assuming a 60 tonne tank with 1g accellaration
	
	
};
