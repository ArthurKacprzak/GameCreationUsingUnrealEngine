// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "RtsSpectatorPawn.generated.h"

class URtsCameraComponent;
class AUnity;

/**
 * 
 */
UCLASS()
class RTSGAME_API ARtsSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<AUnity*> UnitySelected;

	UPROPERTY(VisibleAnywhere)
	TArray<AUnity*> AllUnity;

	UPROPERTY(VisibleAnywhere)
	FVector PressPosition;
	
public:
	ARtsSpectatorPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

public:
	void MoveForward(float value);
	void MoveRight(float value);
	void OnMouseScrollUp();
	void OnMouseScrollDown();

public:
	URtsCameraComponent* CameraComponent;

public:

	void LeftClick();

	void LeftClickReleased();

	void RightClick();

private:
	void UnselectAll();

	bool CheckSelectionBox(float UnityPosX, float one, float two);
};
