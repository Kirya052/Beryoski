// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BTAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKITEST_API UBTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool TryActivateAbilityWithTag(FGameplayTag GameplayTag, bool bAllowRemoteActivation = true);

	bool TryCancelAbilityWithTag(FGameplayTag GameplayTag);

	bool IsAbilityActive(FGameplayTag GameplayTag);
};
