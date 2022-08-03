// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKITEST_API UBTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params | Pawn")
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params | Pawn")
	FVector PawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params | Levels")
	TArray<FName> LevelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params | Levels")
	int32 LevelIndex = 0;

	UFUNCTION(BlueprintCallable)
	FName GetNextLevelName();

	UFUNCTION(BlueprintCallable)
	FName GetFirstLevelName();

	void SaveScore(int32 NewScore);
};
