// Fill out your copyright notice in the Description page of Project Settings.


#include "Interracter.h"

#include "ElecticitySwitch.h"

// Sets default values for this component's properties
UInterracter::UInterracter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInterracter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInterracter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInterracter::Press()
{
	FHitResult HitResult;
	bool HasHit = GetInterractableInReach(HitResult);
	if (HasHit)
		{
			AActor* HitActor = HitResult.GetActor();
			AElecticitySwitch* OurSwitch = Cast<AElecticitySwitch>(HitActor);
			if(OurSwitch->bIsOn == true)
				{			
					OurSwitch->TurnOff();
				}
		}
}


bool UInterracter::GetInterractableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxInterractDistance;
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel1, 
		FCollisionShape::MakeSphere(InterractRadius));
}

