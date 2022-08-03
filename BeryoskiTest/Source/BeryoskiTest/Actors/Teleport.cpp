// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Teleport.h"
#include "BTGameInstance.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ATeleport::ATeleport()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionProfileName("OverlapAll");

	TeleportMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	TeleportMesh->SetupAttachment(BoxCollision);
}

void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	
	BTGameInstance = Cast<UBTGameInstance>(GetWorld()->GetGameInstance());
}

FName ATeleport::GetNextLevelName()
{
	if (BTGameInstance)
	{
		return BTGameInstance->GetNextLevelName();
	}
	return FName();
}

void ATeleport::SaveScore(int32 newScore)
{
	if (BTGameInstance)
	{
		BTGameInstance->SaveScore(newScore);
	}
}

