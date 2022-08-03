// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_ChainLightning.generated.h"

/**
 * 
 */
UCLASS()
class BERYOSKITEST_API UGameplayAbility_ChainLightning : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

protected:
	void StartLightning();
	void TakeDamage();

	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("LightningTrace")), true);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float Radius = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float DamageTime = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float LightningAccurency = 0.1f;

	TArray<class IEnemyInterface*> Enemies;

	FTimerHandle TraceTimer;
	FTimerHandle DamageTimer;

private:
	class APlayerPawn* PlayerPawn;
	FVector TracePosition;
	FRotator TraceRotation;

	int32 ActorIndex = 0;
};

