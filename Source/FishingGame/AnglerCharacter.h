// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AnglerCharacter.generated.h"

UCLASS()
class FISHINGGAME_API AAnglerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnglerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MovementVelocity;

	UPROPERTY(EditAnywhere)
	float CameraSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	// Move Input Actions
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction*  MoveAction;

	// Jump Input Actions
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* CameraPanAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void CameraPan(const FInputActionValue& Value);

	void SetDriveMode(const bool DriveMode);

};
