// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wearable.generated.h"

UCLASS()
class BJD51_API AWearable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWearable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* WearableRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* WearableMesh;


};
