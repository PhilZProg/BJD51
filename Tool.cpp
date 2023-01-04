// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerCharacter.h"




// Sets default values
ATool::ATool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	if (HasHit && ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, Hit.ImpactPoint, ShotDirection.Rotation());
			if (Hit.GetActor() != nullptr)
				{
					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
					AController* OwnerController = GetOwnerContorller();
					AActor* OurPlayerChar = GetOwner();
					APlayerCharacter* OurPlayerCharacter = Cast<APlayerCharacter>(OurPlayerChar);

					if (OurPlayerCharacter->bButtonIsOn && Hit.GetActor()->ActorHasTag(AcceptableTag))
						{
							OurPlayerCharacter->TakeDamage(100, DamageEvent,OwnerController,this);
						}		

					Hit.GetActor()->TakeDamage(Damage, DamageEvent,OwnerController,this);
				}
		}
}

// Called when the game starts or when spawned
void ATool::BeginPlay()
{
	Super::BeginPlay();

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


