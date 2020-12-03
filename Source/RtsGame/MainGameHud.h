// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RtsPlayerController.h"
#include "MainGameHud.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API AMainGameHud : public AHUD
{
	GENERATED_BODY()
public:
	AMainGameHud();

	void BeginPlay() override;
	void Tick(float deltaSeconds) override;

private:
	// Main drawing function
	virtual void DrawHUD() override;
	ARtsPlayerController *GetPlayerController() const;

	void DrawHealthBars() const;
	void DrawSelectionGrid(FVector2D gridStartPos);
	void DrawRessourcesBars();

	float UiScale;
};
