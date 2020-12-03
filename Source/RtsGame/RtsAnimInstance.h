// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RtsAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API URtsAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float characterMovementSpeed_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isCharacterAttacking_;

	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();
};
