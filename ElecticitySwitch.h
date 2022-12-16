// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElecticitySwitch.generated.h"

UCLASS()
class BJD51_API AElecticitySwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElecticitySwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* ButtonRoot;

	UPROPERTY(EditAnywhere)
	class UPointLightComponent* ButtonSignalLight;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ButtonPart1;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ElectroParticles;

};
