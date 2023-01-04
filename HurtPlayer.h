// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "HurtPlayer.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BJD51_API UHurtPlayer : public UBoxComponent
{
	GENERATED_BODY()

	UHurtPlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void AutoHurtTimerReset();
	
	bool bHurting;

	bool bShouldHurt;

	float HurtRate;

	class FTimerManager* Timer;

	FTimerHandle AutoHurtTimer;

	void CheckAndTrigger();

	void Hurting();

	void NotHurting();

	void StartAutoHurtTimer();
};
