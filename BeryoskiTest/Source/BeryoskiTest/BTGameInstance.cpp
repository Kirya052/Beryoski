// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGameInstance.h"

FName UBTGameInstance::GetNextLevelName()
{
	LevelIndex++;
	if (LevelIndex > LevelList.Num())
	{
		return FName();
	}
	return LevelList[LevelIndex];
}

FName UBTGameInstance::GetFirstLevelName()
{
	return LevelList[0];
}

void UBTGameInstance::SaveScore(int32 NewScore)
{
	Score = NewScore;
}
