// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RtsSpectatorPawn.h"
#include "Unity.h"
#include "RtsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ARtsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARtsPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void ProcessPlayerInput(const float deltaTime, const bool bGamePaused) override;

	void MovePawnForward(float value);
	void MovePawnRight(float value);
	void ZoomIn();
	void ZoomOut();


public:

	FVector const& GetSelectionStartPosition() const;

	bool GetIsSelectionActive() const
	{
		return isSelectionActive_;
	}

	void StartSelection()
	{
		FHitResult hit;
		GetHitResultUnderCursor(ECC_Visibility, false, hit);
		selectionStartPosition_ = hit.Location;

		isSelectionActive_ = true;
	}

	void EndSelection()
	{
		FHitResult hit;
		GetHitResultUnderCursor(ECC_Visibility, false, hit);
		selectionEndPosition_ = hit.Location;

		isSelectionActive_ = false;

//		UnitSelection();
	}

public:

	void LeftClick();

	void LeftClickReleased();

	void RightClick();

private:
	bool isSelectionActive_ = false;
	FVector selectionStartPosition_;
	FVector selectionEndPosition_;
};
