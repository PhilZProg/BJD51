// Fill out your copyright notice in the Description page of Project Settings.


#include "ElecticitySwitch.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AElecticitySwitch::AElecticitySwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = ButtonRoot;

	ButtonPart1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	ButtonPart1->SetupAttachment(ButtonRoot);

	ButtonSignalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Signal Light"));
	ButtonSignalLight->SetupAttachment(ButtonRoot);

	ElectroParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Electro Particles"));
	ElectroParticles->SetupAttachment(ButtonRoot);

}

// Called when the game starts or when spawned
void AElecticitySwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElecticitySwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElecticitySwitch::TurnOff()
{
		ButtonSignalLight->SetLightFColor(FColor::Red);
		ElectroParticles->DestroyComponent();
		bIsOn = false;
}