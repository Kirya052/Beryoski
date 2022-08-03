// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKITEST_API UScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateScore(int32 newScore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score = 0;
};
