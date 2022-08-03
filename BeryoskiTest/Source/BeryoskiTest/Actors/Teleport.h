// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

UCLASS()
class BERYOSKITEST_API ATeleport : public AActor
{
	GENERATED_BODY()
	
public:
	ATeleport();

	UFUNCTION(BlueprintCallable)
	FName GetNextLevelName();

	UFUNCTION(BlueprintCallable)
	void SaveScore(int32 newScore);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TeleportMesh;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UBTGameInstance* BTGameInstance;
};
