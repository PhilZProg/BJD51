// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickUpRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = PickUpRoot;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(PickUpRoot);

	SignalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Signal Light"));
	SignalLight->SetupAttachment(PickUpRoot);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

