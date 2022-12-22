// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interracter.h"
#include "Tool.h"
#include "Checker.h"
#include "Math.h"
#include "FireFightGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	//SpringArmComp->bUsePawnControlRotation = true; 
	SpringArmComp->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Interracter = CreateDefaultSubobject<UInterracter>(TEXT("Interracter"));
	Interracter->SetupAttachment(CameraComp);

	Checker = CreateDefaultSubobject<UChecker>(TEXT("Checker"));
	Checker->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));

	Health = MaxHealth;

	ShootRate = 0.2f;	

	bShouldShoot = true;

	bShooting = false;

	bDead = false;

	bCrouch = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraDefFOV = CameraComp->FieldOfView;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);


	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Shooting);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &APlayerCharacter::NotShooting);


	PlayerInputComponent->BindAction(TEXT("Interract"),EInputEvent::IE_Pressed, this, &APlayerCharacter::Interract);


	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &APlayerCharacter::MoveForward);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis(TEXT("LookRight"),this, &APawn::AddControllerYawInput);


	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Aim);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &APlayerCharacter::UnAim);


	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Crouching);

}

void APlayerCharacter::Shooting()
{
	if (!bDead && !bCrouch)
	{
		bShooting = true;
		StartAutoShootTimer();
	}
} 

void APlayerCharacter::NotShooting()
{
	if (!bDead)
		{
			bShooting = false;
		}
}

void APlayerCharacter::Jump()
{
	if (!bDead)
		{
			ACharacter::Jump();
		}
}

void APlayerCharacter::StartAutoShootTimer()
{
	if (!bDead)
		{
			if (bShouldShoot)
				{
					AActor* OurTool = Checker->CheckAndTrigger();

					if (OurTool != nullptr && bAiming)
						{
							Tool = Cast<ATool>(OurTool);
							Tool->Fire();
							bShouldShoot = false;
							GetWorldTimerManager().SetTimer(
								AutoShootTimer, 
								this, 
								&APlayerCharacter::AutoShootTimerReset, 
								ShootRate);
						}
				}
		}
}

void APlayerCharacter::AutoShootTimerReset()
{
	if (!bDead)
		{
			bShouldShoot = true;
			if (bShooting)
				{
					StartAutoShootTimer();
				}
		}
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!bDead)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// add movement
			AddMovementInput(ForwardDirection, AxisValue);
		}
	
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (!bDead)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement
			AddMovementInput(RightDirection, AxisValue);
		}
	
}

void APlayerCharacter::Interract()
{	
	if (!bDead)
		{
			Interracter->Press();
		}
	
}

void APlayerCharacter::Aim()
{	
	if (!bDead && !bCrouch && bHasTool)
		{
			bAiming = true;

			CameraComp->FieldOfView = CameraZoomedFOV;

			bUseControllerRotationPitch = true;
			bUseControllerRotationYaw = true;
			bUseControllerRotationRoll = true;
		}
	
}  

void APlayerCharacter::UnAim()
{	
			bAiming = false;

			CameraComp->FieldOfView = CameraDefFOV;

			bUseControllerRotationPitch = false;
			bUseControllerRotationYaw = false;
			bUseControllerRotationRoll = false;

			PlayerRotation = GetActorRotation();
			PlayerRotation.Pitch = 0;

			SetActorRotation(PlayerRotation);
} 

void APlayerCharacter::Crouching()
{
	if (!bCrouch)
		{
			bCrouch = true;
			GetCharacterMovement()->MaxWalkSpeed = 250.f; 
		}
	else
		{
			bCrouch = false;
			GetCharacterMovement()->MaxWalkSpeed = 600.f; 
		}
	
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);

	Health -= DamageToApply;

	if(IsDead())
		{
			bDead = true;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
			APawn* Player = Cast<APawn>(this);
            AController* PlayerController = Player->GetController();
            PlayerController->GameHasEnded(Player, false);
	  	}

	return DamageToApply;
}

bool APlayerCharacter::IsDead() const
{
	return Health <= 0;
}

bool APlayerCharacter::IsCrouching() const
{
	return bCrouch;
}

bool APlayerCharacter::IsAiming() const
{
	return bAiming;
}

float APlayerCharacter::GetCurrentHealth() const
{
	return Health / MaxHealth;
}