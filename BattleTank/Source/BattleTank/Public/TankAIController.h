// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	void BeginPlay() override;
	
	ATank* GetPlayerTank() const;
};
