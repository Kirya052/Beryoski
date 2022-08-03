// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyActor.h"
#include "Components/BoxComponent.h"


AEnemyActor::AEnemyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionProfileName("BlockAll");

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);
}

void AEnemyActor::Died()
{
	SetBridgeHidden(false);
	Destroy();
}

FVector AEnemyActor::GetPosition()
{
	return GetActorLocation();
}

void AEnemyActor::SetBridgeHidden(bool bIsHidden)
{
	if (IsValid(Bridge))
	{
		Bridge->SetActorHiddenInGame(bIsHidden);
		Bridge->SetActorEnableCollision(!bIsHidden);
	}
}

void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	SetBridgeHidden(true);
}
