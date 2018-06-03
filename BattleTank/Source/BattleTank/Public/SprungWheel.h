// Copyright Michail Paschou

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Setup)
		USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Setup)
		USphereComponent* Axel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Setup)
		UPhysicsConstraintComponent* Spring = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Setup)
		UPhysicsConstraintComponent* WheelAxel = nullptr;

private:
	void SetupConstraints();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float TotalForceMagnitudeThisFrame;

	void ApplyForce();
};
