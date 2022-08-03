// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Move.h"
#include "Pawn\PlayerPawn.h"
#include "Components\SphereComponent.h"
#include "Components\ArrowComponent.h"

bool UGameplayAbility_Move::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!ActorInfo->AvatarActor->IsA<APlayerPawn>())
	{
		return false;
	}

	APlayerPawn* CachedPawn = StaticCast<APlayerPawn*>(ActorInfo->AvatarActor.Get());
	return CachedPawn->CanMove();
}

void UGameplayAbility_Move::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	GetWorld()->GetTimerManager().SetTimer(ForceTimer, this, &UGameplayAbility_Move::AddForceMultiply, ChangeForceSpeed, true);
}

void UGameplayAbility_Move::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	GetWorld()->GetTimerManager().ClearTimer(ForceTimer);

	APlayerPawn* CachedPawn = StaticCast<APlayerPawn*>(ActorInfo->AvatarActor.Get());
	USphereComponent* SphereCollision = CachedPawn->GetRootSphere();

	FVector forwardVector = CachedPawn->GetArrowComponent()->GetForwardVector();
	FVector ForceVector = forwardVector * ForceMultiply * Force;
	SphereCollision->AddForce(ForceVector, NAME_None, true);

	ForceMultiply = 1;

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGameplayAbility_Move::AddForceMultiply()
{
	ForceMultiply++;

	if (ForceMultiply > MaxForceMultiply)
	{
		K2_CancelAbility();
	}
}
