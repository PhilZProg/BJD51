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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	bool IsCrouching() const;

	UFUNCTION(BlueprintPure)
	bool IsAiming() const;

	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;

	bool bButtonIsOn = true;

	bool bHasTool = false;

	bool bCrouch{};

	bool bWearingCloth = false;

	bool bDead;

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

	bool bAiming = false;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health{};

	float CameraDefFOV{};

	FRotator PlayerRotation;

	float CameraZoomedFOV = 60.f;

	bool bShooting;

	bool bShouldShoot;

	float ShootRate;

	FTimerHandle AutoShootTimer;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Interract();

	void Aim();

	void UnAim();

	void Crouching();

	void Shooting();

	void NotShooting();

	void Jump();

	void StartAutoShootTimer();

	UFUNCTION()
	void AutoShootTimerReset();
};
