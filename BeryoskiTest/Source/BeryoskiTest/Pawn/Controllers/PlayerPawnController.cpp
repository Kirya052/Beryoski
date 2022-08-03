// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"
#include "Pawn\PlayerPawn.h"

void APlayerPawnController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedPawn = Cast<APlayerPawn>(InPawn);
}

void APlayerPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("RotateRight", this, &APlayerPawnController::RotateRight);
	InputComponent->BindAction("ChangeForce", EInputEvent::IE_Pressed, this, &APlayerPawnController::ChangeForce);
	InputComponent->BindAction("Move", EInputEvent::IE_Released, this, &APlayerPawnController::Move);
	InputComponent->BindAction("SpecialAbility", EInputEvent::IE_Pressed, this, &APlayerPawnController::SpecialAbility);
}

void APlayerPawnController::Move()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->CancelMovementAbility();
	}
}

void APlayerPawnController::ChangeForce()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->ActivateMovementAbility();
	}
}

void APlayerPawnController::RotateRight(float Value)
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->RotateRight(Value);
	}
}

void APlayerPawnController::SpecialAbility()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->SpecialAbility();
	}
}
