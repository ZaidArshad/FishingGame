// Fill out your copyright notice in the Description page of Project Settings.


#include "AnglerBoat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AAnglerBoat::AAnglerBoat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementVelocity = 1.0f;
	CameraSensitivity = 1.0f;
}

// Called when the game starts or when spawned
void AAnglerBoat::BeginPlay()
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
void AAnglerBoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnglerBoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnglerBoat::Move);
		EnhancedInputComponent->BindAction(CameraPanAction, ETriggerEvent::Triggered, this, &AAnglerBoat::CameraPan);
	}
}

void AAnglerBoat::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(MovementValue.Y);

		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue.X * MovementVelocity);
	}
}

void AAnglerBoat::CameraPan(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>() * CameraSensitivity;

	if (Controller)
	{
		AddControllerYawInput(MovementValue.X);
		AddControllerPitchInput(-MovementValue.Y);
	}
}

