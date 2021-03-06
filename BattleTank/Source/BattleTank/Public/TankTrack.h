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
	UTankTrack();

	virtual void BeginPlay() override;

	//void ApplySidewaysForce();

	//UFUNCTION()
	//	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BLueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);

	//Max Force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float TrackMaxDrivingForce = 60000000;	//Assuming a 60 tonne tank with 1g accellaration
	
private:
	TArray <class ASprungWheel*> GetWheels() const;
};
