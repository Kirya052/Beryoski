// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "PlayerPawn.generated.h"

class USphereComponent;
class UArrowComponent;
class UScoreUserWidget;
UCLASS()
class BERYOSKITEST_API APlayerPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerPawn();

	virtual void PossessedBy(AController* NewController);

	void ActivateMovementAbility();
	void CancelMovementAbility();

	void RotateRight(float Value);

	bool CanMove();

	void SpecialAbility();

	USphereComponent* GetRootSphere() { return SphereCollision; };
	UArrowComponent* GetArrowComponent() { return ArrowComponent; };

	bool bCanActivateSpecialAbility = true;

	// Score
	
	void AddScore();

	UFUNCTION(BlueprintCallable)
	int32 GetScore() { return Score; };

	// ~Score

	/**	IAbilitySystemInterface */
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/**	~IAbilitySystemInterface */
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components | Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components | Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ArrowComponent;

	// Score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UScoreUserWidget> ScoreWidgetClass;

	UScoreUserWidget* ScoreWidget;

	int32 Score = 0;

	void InitializeScoreAndPosition();
	// ~Score

	// AbilitySystem
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UBTAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	FGameplayTag MovementAbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	FGameplayTag SpecialAbilityTag;

	void InitGameplayAbilitySystem(AController* NewController);
	// ~ AbilitySystem

private:
	bool bIsAbilitiesInitialized = false;

};
