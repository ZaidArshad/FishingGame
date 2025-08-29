// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Pawn.h"
#include "AnglerBoat.generated.h"

UCLASS()
class FISHINGGAME_API AAnglerBoat : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnglerBoat();

	UPROPERTY(EditAnywhere)
	float MovementVelocity;

	UPROPERTY(EditAnywhere)
	float CameraSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	// Move Input Actions
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* CameraPanAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void CameraPan(const FInputActionValue& Value);
};
