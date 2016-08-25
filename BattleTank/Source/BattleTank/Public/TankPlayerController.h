// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //must be the last includes

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
		
	void AimTowardsCrosshair();

	//Return Out parameter, True if hits landscape.
	bool GetSightHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.333333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0;
};
