// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
	void HandleDestruction();

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotateSpeed = 30.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Trun(float Value);

	class APlayerController* TankPlayerController;

};
