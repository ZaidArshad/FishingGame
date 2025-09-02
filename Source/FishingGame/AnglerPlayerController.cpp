// Fill out your copyright notice in the Description page of Project Settings.


#include "AnglerPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AAnglerPlayerController::AAnglerPlayerController()
{
	IsDriving = false;
}

// Called when the game starts or when spawned
void AAnglerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AAnglerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(DriveAction, ETriggerEvent::Triggered, this, &AAnglerPlayerController::ToggleDrive);
	}
}

void AAnglerPlayerController::ToggleDrive()
{
	IsDriving = !IsDriving;
	AnglerCharacter = Cast<AAnglerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AAnglerCharacter::StaticClass()));
	AnglerBoat = Cast<AAnglerBoat>(UGameplayStatics::GetActorOfClass(GetWorld(), AAnglerBoat::StaticClass()));

	if (IsDriving)
	{
		UE_LOG(LogTemp, Display, TEXT("Possess boat %f"), AnglerBoat->GetActorLocation().X);
		Possess(AnglerBoat);
		FAttachmentTransformRules AttachmentRule(EAttachmentRule::KeepWorld, true);
		AnglerCharacter->AttachToActor(AnglerBoat, AttachmentRule);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Possess character %f"), AnglerCharacter->GetActorLocation().X);
		Possess(AnglerCharacter);
		AnglerCharacter->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	AnglerCharacter->SetDriveMode(IsDriving);
}