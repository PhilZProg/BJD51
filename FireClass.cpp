// Fill out your copyright notice in the Description page of Project Settings.


#include "FireClass.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFireClass::AFireClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	Health = MaxHealth;
}

// Called every frame
void AFireClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFireClass::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);

	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), Health);

	 if(IsDead())
	 	{
			
			Destroy();
	// 		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
			
	// 		if (GameMode != nullptr)
	// 			{
	// 				GameMode->PawnKilled(this);
	// 			}

	// 		DetachFromControllerPendingDestroy();
			
	// 		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	 	}

	return DamageToApply;
}

bool AFireClass::IsDead() const
{
	return Health <= 0;
}

float AFireClass::GetCurrentHealth() const
{
	return Health / MaxHealth;
}