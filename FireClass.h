// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireClass.generated.h"

UCLASS()
class BJD51_API AFireClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* FireRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* FireCapsule;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* FireParticles;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health{};

};
