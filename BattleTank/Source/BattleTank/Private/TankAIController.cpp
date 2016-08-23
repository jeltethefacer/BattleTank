// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	auto ControlledTank = GetControlledTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s did found %s"), *ControlledTank->GetName(), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s did not found the PlayerTank"), *ControlledTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(PlayerPawn){
		return Cast<ATank>(PlayerPawn);
	}
	else
	{
		return nullptr;
	}
}


