// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class BJD51_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* PickUpRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UPointLightComponent* SignalLight;
};
