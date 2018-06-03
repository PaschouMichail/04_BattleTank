// Copyright Michail Paschou

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"


UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadius = 8000.f;
	
private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnMortarDeath();
	
};
