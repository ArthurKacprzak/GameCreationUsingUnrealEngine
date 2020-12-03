// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "RtsPlayerController.h"
#include "RtsCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API URtsCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:
	URtsCameraComponent();

	virtual void GetCameraView(float deltaTime, FMinimalViewInfo& desiredView) override;

	void OnZoomIn();
	void OnZoomOut();
	void UpdateCameraMovement(const APlayerController* playerController) const;
	void MoveForward(float value) const;
	void MoveRight(float value) const;
	void SetZoomLevel(float level);

private:
	float minCameraOffset_;
	float maxCameraOffset_;
	FRotator fixedCameraAngle_;

	float cameraScrollSpeed_;
	uint32 cameraActiveBorder_;
	float minZoomLevel_;
	float maxZoomLevel_;
	float zoomAlpha_;
	float movementSpeed_;

	bool bShouldClampCamera_ : 1;

	FBox cameraMovementBounds_;
	FVector2D cameraMovementViewportSize_;

	APawn* GetOwnerPawn() const;
};
