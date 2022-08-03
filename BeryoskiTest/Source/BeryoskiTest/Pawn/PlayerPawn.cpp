// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PlayerPawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "AbilitySystem/BTAbilitySystemComponent.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SphereMesh->SetupAttachment(SphereCollision);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SphereCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(SphereCollision);
	ArrowComponent->SetHiddenInGame(false);

	AbilitySystemComponent = CreateDefaultSubobject<UBTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void APlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitGameplayAbilitySystem(NewController);
}

void APlayerPawn::ActivateMovementAbility()
{
	AbilitySystemComponent->TryActivateAbilityWithTag(MovementAbilityTag);
}

void APlayerPawn::CancelMovementAbility()
{
	AbilitySystemComponent->TryCancelAbilityWithTag(MovementAbilityTag);
}

void APlayerPawn::RotateRight(float Value)
{
	FRotator ArrowRotation = ArrowComponent->GetRelativeRotation();
	FRotator NewRotation = ArrowRotation + FRotator(0.0f, Value, 0.0f);
	ArrowComponent->SetWorldRotation(FMath::Lerp(NewRotation, ArrowRotation, 0.1f));
}

bool APlayerPawn::CanMove()
{
	bool bCanMove = false;

	if (SphereCollision->GetPhysicsLinearVelocity().X > 0.01f)
	{
		bCanMove = false;
	}
	else
	{
		bCanMove = true;
	}

	return bCanMove;
}

void APlayerPawn::SpecialAbility()
{
	AbilitySystemComponent->TryActivateAbilityWithTag(SpecialAbilityTag);
}

UAbilitySystemComponent* APlayerPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerPawn::InitGameplayAbilitySystem(AController* NewController)
{
	AbilitySystemComponent->InitAbilityActorInfo(NewController, this);

	if (!bIsAbilitiesInitialized)
	{
		for (TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass));
		}
		bIsAbilitiesInitialized = true;
	}
}
