// Fill out your copyright notice in the Description page of Project Settings.


#include "AnglerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h" 

// Sets default values
AAnglerCharacter::AAnglerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementVelocity = 1.0f;
	CameraSensitivity = 1.0f;
}

// Called when the game starts or when spawned
void AAnglerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AAnglerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnglerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnglerCharacter::Move);
		EnhancedInputComponent->BindAction(CameraPanAction, ETriggerEvent::Triggered, this, &AAnglerCharacter::CameraPan);

	}

}

void AAnglerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>() * MovementVelocity;

	if (Controller)
	{
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementValue.Y);

		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue.X);
	}
}

void AAnglerCharacter::CameraPan(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>() * CameraSensitivity;

	if (Controller)
	{
		AddControllerYawInput(MovementValue.X);
		AddControllerPitchInput(-MovementValue.Y);
	}
}

void AAnglerCharacter::SetDriveMode(const bool DriveMode)
{
	if (DriveMode)
	{
		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}

	SetActorEnableCollision(!DriveMode);
}
