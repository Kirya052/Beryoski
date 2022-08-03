// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Move.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKITEST_API UGameplayAbility_Move : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

protected:
	FTimerHandle ForceTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	float Force = 10000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	int ForceMultiply = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	int MaxForceMultiply = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Force")
	float ChangeForceSpeed = 0.5f;

	void AddForceMultiply();
};
