// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "RtsSpectatorPawn.h"
#include "RtsCameraComponent.h"
#include "AIController.h"


ARtsPlayerController::ARtsPlayerController() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
//	bHidden = false;
	this->bShowMouseCursor = true;

}

void ARtsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARtsPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARtsPlayerController::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &ARtsPlayerController::MovePawnForward);
	InputComponent->BindAxis("MoveRight", this, &ARtsPlayerController::MovePawnRight);

	InputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Pressed, this, &ARtsPlayerController::LeftClick);
	InputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Released, this, &ARtsPlayerController::LeftClickReleased);
	InputComponent->BindAction("MouseRightClick", EInputEvent::IE_Pressed, this, &ARtsPlayerController::RightClick);
}

void ARtsPlayerController::ProcessPlayerInput(const float deltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(deltaTime, bGamePaused);

	{
		const ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player);
		ARtsSpectatorPawn *spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn());

		if (spectatorPawn && localPlayer)
		{
			if (localPlayer->ViewportClient)
			{
				spectatorPawn->CameraComponent->UpdateCameraMovement(this);
			}
		}
	}
}

void ARtsPlayerController::MovePawnForward(const float value)
{
	ARtsSpectatorPawn* spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->MoveForward(value);
	}
}

void ARtsPlayerController::MovePawnRight(const float value)
{
	ARtsSpectatorPawn* spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->MoveRight(value);
	}
}

void ARtsPlayerController::ZoomIn()
{
	if (GetPawn()) {
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, GetPawn()->GetName(), false);
	}
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollUp();
	}
}

void ARtsPlayerController::ZoomOut()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollDown();
	}
}

FVector const& ARtsPlayerController::GetSelectionStartPosition() const
{
	return selectionStartPosition_;
}



void ARtsPlayerController::LeftClick()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->LeftClick();
	}
}

void ARtsPlayerController::LeftClickReleased()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->LeftClickReleased();
	}
}

void ARtsPlayerController::RightClick()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->RightClick();
	}
}