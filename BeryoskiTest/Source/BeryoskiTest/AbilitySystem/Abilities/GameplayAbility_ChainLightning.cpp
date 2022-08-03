// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_ChainLightning.h"
#include "Pawn\PlayerPawn.h"
#include "Components\ArrowComponent.h"
#include "Interfaces\EnemyInterface.h"
#include "Kismet\KismetMathLibrary.h"

bool UGameplayAbility_ChainLightning::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/, const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
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
	return CachedPawn->bCanActivateSpecialAbility;
}

void UGameplayAbility_ChainLightning::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	PlayerPawn = StaticCast<APlayerPawn*>(OwnerInfo->AvatarActor.Get());
	PlayerPawn->bCanActivateSpecialAbility = false;
	TracePosition = PlayerPawn->GetActorLocation();
	TraceRotation = PlayerPawn->GetArrowComponent()->GetComponentRotation();

	GetWorld()->GetTimerManager().SetTimer(TraceTimer, this, &UGameplayAbility_ChainLightning::StartLightning, 0.00001f, true, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(DamageTimer, this, &UGameplayAbility_ChainLightning::TakeDamage, DamageTime, true, 0.1f);
}

void UGameplayAbility_ChainLightning::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	PlayerPawn->bCanActivateSpecialAbility = true;
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGameplayAbility_ChainLightning::StartLightning()
{
	TraceRotation += FRotator(0.0f, LightningAccurency, 0.0f);

	FHitResult hitResult;

	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;
	traceParams.AddIgnoredActor(PlayerPawn);

	FVector EndPosition = UKismetMathLibrary::GetForwardVector(TraceRotation) * Radius + TracePosition;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, TracePosition, EndPosition, ECollisionChannel::ECC_Visibility, traceParams))
	{
		//DrawDebugLine(GetWorld(), TracePosition, EndPosition, FColor::Red, false, 0.5f, 0, 5);

		if (hitResult.GetActor())
		{
			traceParams.AddIgnoredActor(hitResult.GetActor());

			IEnemyInterface* Enemy = Cast<IEnemyInterface>(hitResult.GetActor());
			if (Enemy)
			{
				Enemies.Add(Enemy);
			}
		}
	}
	/*else
	{
		DrawDebugLine(GetWorld(), TracePosition, EndPosition, FColor::Green, false, 2.0f, 0, 5);
	} */
}

void UGameplayAbility_ChainLightning::TakeDamage()
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimer);

	if (ActorIndex >= Enemies.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimer);
		K2_CancelAbility();
		return;
	}

	DrawDebugLine(GetWorld(), PlayerPawn->GetActorLocation(), Enemies[ActorIndex]->GetPosition(), FColor::Purple, false, DamageTime, 0, 5);
	Enemies[ActorIndex]->Died();
	PlayerPawn->AddScore();
	ActorIndex++;
}
