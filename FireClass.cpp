// Fill out your copyright notice in the Description page of Project Settings.


#include "FireClass.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerCharacter.h"
#include "Smoke.h"

// Sets default values
AFireClass::AFireClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FireRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Root"));
	RootComponent = FireRoot;

	FireCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Fire Capsule"));
	FireCapsule->SetupAttachment(FireRoot);

	FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particles"));
	FireParticles->SetupAttachment(FireRoot);

}

// Called when the game starts or when spawned
void AFireClass::BeginPlay()
{
	Super::BeginPlay();
}

float AFireClass::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{	

	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);

	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Fire Health: %f"), Health);

	 if(IsDead())
	 	{
			DamageCauser->Destroy();
			APawn* Pers = EventInstigator->GetPawn();
			APlayerCharacter* OurPlayerCharacter = Cast<APlayerCharacter>(Pers);
        	OurPlayerCharacter->bHasTool = false;

			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation1, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation2, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation3, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation4, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation5, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation6, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation7, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation8, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation9, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation10, SmokeRotation);
			GetWorld()->SpawnActor<ASmoke>(SmokeClass, SmokeLocation11, SmokeRotation);
			
			Destroy();
	 	}

	return DamageToApply;
}

bool AFireClass::IsDead() const
{
	return Health <= 0;
}