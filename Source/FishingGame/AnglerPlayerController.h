// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnglerBoat.h"
#include "AnglerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "AnglerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FISHINGGAME_API AAnglerPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere)
	bool IsDriving;

	AAnglerBoat* AnglerBoat;
	AAnglerCharacter* AnglerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	// Move Input Actions
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* DriveAction;

	AAnglerPlayerController();
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void CameraPan(const FInputActionValue& Value);

	void ToggleDrive();
};
