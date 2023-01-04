// Fill out your copyright notice in the Description page of Project Settings.


#include "Smoke.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASmoke::ASmoke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SmokeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Smoke Root"));
	RootComponent = SmokeRoot;

	SmokeParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particles"));
	SmokeParticles->SetupAttachment(SmokeRoot);

}

// Called when the game starts or when spawned
void ASmoke::BeginPlay()
{
	Super::BeginPlay();
	
}

