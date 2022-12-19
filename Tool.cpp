// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool.h"
//#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"



// Sets default values
ATool::ATool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ToolRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Tool Root"));
	RootComponent = ToolRoot;

	ToolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tool Mesh"));
	ToolMesh->SetupAttachment(ToolRoot);

	FoamSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Foam Spawn Point"));
	FoamSpawnPoint->SetupAttachment(ToolMesh);


}

void ATool::Fire()
{

	if (FoamErupt)
		{ 
			UGameplayStatics::SpawnEmitterAtLocation(this, FoamErupt, FoamSpawnPoint->GetComponentLocation());
		}

	FHitResult Hit; 
	FVector ShotDirection;
	bool HasHit = ToolTrace(Hit, ShotDirection);

	// FHitResult Hit2;
	// const FVector Hit2TraceStart{FoamSpawnPoint->GetComponentLocation()};
	// const FVector Hit2TraceEnd{FoamSpawnPoint->GetComponentLocation()};
	

	if (HasHit && ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, Hit.ImpactPoint, ShotDirection.Rotation());
			if (Hit.GetActor() != nullptr)
				{
					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
					AController* OwnerController = GetOwnerContorller();
					Hit.GetActor()->TakeDamage(Damage, DamageEvent,OwnerController,this);
				}
		}
}

// Called when the game starts or when spawned
void ATool::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ATool::ToolTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerContorller();
	if (OwnerController == nullptr)
		{
			return false;
		}
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End =Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	DrawDebugLine(GetWorld(),FoamSpawnPoint->GetComponentLocation(),End, FColor::Red, false, 2.f);
	return GetWorld()->LineTraceSingleByChannel(Hit,FoamSpawnPoint->GetComponentLocation(), End, ECC_Visibility, Params);

}

AController* ATool::GetOwnerContorller() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		{
			return nullptr;
		}
	return OwnerPawn->GetController();	
}


