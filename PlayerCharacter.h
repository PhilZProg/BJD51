// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class BJD51_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	class UInterracter* Interracter;

	UPROPERTY(EditAnywhere)
	class UChecker* Checker;

	UPROPERTY()
	class ATool* Tool;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATool> ToolClass;

	UPROPERTY(VisibleAnywhere)
	bool bAiming = false;

	float CameraDefFOV{};

	UCapsuleComponent* Capsule;

	FRotator CapsulesRotation;

	float CameraZoomedFOV = 60.f;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Interract();

	void Aim();

	void UnAim();
};
