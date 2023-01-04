// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "HeadWearTrigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BJD51_API UHeadWearTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeadWearTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;

	UPROPERTY()
	class AWearable* HeadWeard;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWearable> HeadWeardClass;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CheckAndTrigger();
};
