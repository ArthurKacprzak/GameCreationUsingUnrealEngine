// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsAnimInstance.h"
#include "Unity.h"

void URtsAnimInstance::UpdateAnimationProperties()
{
	const APawn* character = TryGetPawnOwner();
	const AUnity* Unity;

	if (character && (Unity = Cast<AUnity>(character)) != nullptr)
	{
//		isCharacterAttacking_ = Unity->GetIsAttacking();
		characterMovementSpeed_ = Unity->GetSpeed();
	}
}