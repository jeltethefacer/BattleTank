// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not possesing a tank"));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is Possesing: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation;
	if (GetSightHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		//TODO tell controlled Tank to aim at this point
	}
}

//GetWorld Location if linetrace through crosshair
bool ATankPlayerController::GetSightHitLocation(FVector& HitLocation) const
{
	//find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	
	//"De-project" the screen position of the crosshair to a world directoin
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-Trace along that look direction, and see what we hit
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection (FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	
	if(UWorld().LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}