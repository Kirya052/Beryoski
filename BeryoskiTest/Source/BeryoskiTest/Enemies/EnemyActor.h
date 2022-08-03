// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/EnemyInterface.h"
#include "EnemyActor.generated.h"


UCLASS()
class BERYOSKITEST_API AEnemyActor : public AActor, public IEnemyInterface
{
	GENERATED_BODY()
	
public:	
	AEnemyActor();

	virtual void Died() override;
	virtual FVector GetPosition() override;

	void SetBridgeHidden(bool bIsHidden);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bridge")
	AActor* Bridge;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BodyMesh;
};
