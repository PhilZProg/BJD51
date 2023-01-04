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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASmoke> SmokeClass;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* FireRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* FireCapsule;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* FireParticles;

	UPROPERTY(EditDefaultsOnly)
	float Health = 100;

	FRotator SmokeRotation {180.f, 0.f, 180.f};

	const FVector SmokeLocation1 {1812.042019, 211.180450, 200};
	const FVector SmokeLocation2 {2187.042019, 211.180450, 200};
	const FVector SmokeLocation3 {2187.042019, 566.180450, 200};
	const FVector SmokeLocation4 {2187.042019, 921.180450, 200};
	const FVector SmokeLocation5 {2187.042019, 1276.180450, 200};
	const FVector SmokeLocation6 {2187.042019, 1631.180450, 200};
	const FVector SmokeLocation7 {2187.042019, 1986.180450, 200};
	const FVector SmokeLocation8 {2187.042019, 2341.180450, 200};
	const FVector SmokeLocation9 {2557.042019, 2206.180450, 200};
	const FVector SmokeLocation10 {2557.042019, 2561.180450, 200};
	const FVector SmokeLocation11 {2187.042019, 2561.180450, 200};

};
