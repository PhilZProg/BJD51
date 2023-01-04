// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tool.generated.h"


UCLASS()
class BJD51_API ATool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATool();
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame

	void Fire();

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* ToolRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* ToolMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* FoamSpawnPoint;

	UPROPERTY(EditAnywhere)
	UParticleSystem* FoamErupt;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;
 
	UPROPERTY(EditAnywhere)
	float MaxRange = 500;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	bool ToolTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerContorller() const;

	UPROPERTY(EditAnywhere)
	FName AcceptableTag;
};
