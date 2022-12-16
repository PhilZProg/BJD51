// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PowerOffTrigger.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BJD51_API UPowerOffTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	UPowerOffTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;

	// UPROPERTY()
	// class ATool* Tool;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<ATool> ToolClass;

	void CheckAndTrigger();
	
};
