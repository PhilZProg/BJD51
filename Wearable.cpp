// Fill out your copyright notice in the Description page of Project Settings.


#include "Wearable.h"

// Sets default values
AWearable::AWearable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WearableRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Wearable Root"));
	RootComponent = WearableRoot;

	WearableMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wearable Mesh"));
	WearableMesh->SetupAttachment(WearableRoot);

}

// Called when the game starts or when spawned
void AWearable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWearable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

