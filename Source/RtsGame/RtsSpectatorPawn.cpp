// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsSpectatorPawn.h"
#include "RtsCameraComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Unity.h"
#include "AIController.h"

ARtsSpectatorPawn::ARtsSpectatorPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bAddDefaultMovementBindings = false;

	CameraComponent = CreateDefaultSubobject<URtsCameraComponent>(TEXT("Camera Component"));
	


	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AUnity::StaticClass(), FoundActors);

	for (auto& Actor : FoundActors)
	{
		AUnity* tmpUnity = Cast<AUnity>(Actor);
		if (tmpUnity) {
			this->AllUnity.Add(tmpUnity);
		}
	}
}

void ARtsSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector::ZeroVector);
}

void ARtsSpectatorPawn::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ARtsSpectatorPawn::MoveForward(const float value)
{
	if (value != 0.f)
	{
		CameraComponent->MoveForward(value);
	}
}

void ARtsSpectatorPawn::MoveRight(const float value)
{
	if (value != 0.f)
	{
		CameraComponent->MoveRight(value);
	}
}

void ARtsSpectatorPawn::OnMouseScrollUp()
{
	CameraComponent->OnZoomIn();
}

void ARtsSpectatorPawn::OnMouseScrollDown()
{
	CameraComponent->OnZoomOut();
}



void ARtsSpectatorPawn::LeftClick()
{
	FHitResult Hit;
	Controller->CastToPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {


			this->PressPosition = Hit.ImpactPoint;

			this->UnselectAll();

			ARtsPlayerController* pc = Cast<ARtsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			pc->StartSelection();
		}
	}
}

void ARtsSpectatorPawn::LeftClickReleased()
{
	FHitResult Hit;
	Controller->CastToPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {
			if (this->PressPosition != FVector(0.f, 0.f, 0.f)) {
				this->UnselectAll();


				AUnity* UnityTmp = Cast<AUnity>(Hit.GetActor());

				if (UnityTmp) {
					this->UnitySelected.Add(UnityTmp);
					UnityTmp->Select();
				}

				FVector ImpactPoint = Hit.ImpactPoint;
				bool SelectedBoxUp = false;
				bool SelectedBoxRight = false;

				if (this->PressPosition.X < ImpactPoint.X) {
					SelectedBoxUp = true;
				}
				if (this->PressPosition.Y < ImpactPoint.Y) {
					SelectedBoxRight = true;
				}
				for (auto& Unity : this->AllUnity) {
					if (SelectedBoxUp && SelectedBoxRight
						&& this->CheckSelectionBox(Unity->GetActorLocation().X, ImpactPoint.X, this->PressPosition.X)
						&& this->CheckSelectionBox(Unity->GetActorLocation().Y, ImpactPoint.Y, this->PressPosition.Y)) {
						this->UnitySelected.Add(Unity);
						Unity->Select();
					}

					if (SelectedBoxUp && !SelectedBoxRight
						&& this->CheckSelectionBox(Unity->GetActorLocation().X, ImpactPoint.X, this->PressPosition.X)
						&& this->CheckSelectionBox(Unity->GetActorLocation().Y, this->PressPosition.Y, ImpactPoint.Y)) {
						this->UnitySelected.Add(Unity);
						Unity->Select();
					}

					if (!SelectedBoxUp && SelectedBoxRight
						&& this->CheckSelectionBox(Unity->GetActorLocation().X, this->PressPosition.X, ImpactPoint.X)
						&& this->CheckSelectionBox(Unity->GetActorLocation().Y, ImpactPoint.Y, this->PressPosition.Y)) {
						this->UnitySelected.Add(Unity);
						Unity->Select();
					}

					if (!SelectedBoxUp && !SelectedBoxRight
						&& this->CheckSelectionBox(Unity->GetActorLocation().X, this->PressPosition.X, ImpactPoint.X)
						&& this->CheckSelectionBox(Unity->GetActorLocation().Y, this->PressPosition.Y, ImpactPoint.Y)) {
						this->UnitySelected.Add(Unity);
						Unity->Select();
					}

				}
			}

			ARtsPlayerController* pc = Cast<ARtsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			pc->EndSelection();

		}
	}
}

bool ARtsSpectatorPawn::CheckSelectionBox(float UnityPosX, float one, float two)
{
	return UnityPosX > two && UnityPosX < one;
}

void ARtsSpectatorPawn::RightClick()
{
	FHitResult Hit;
	Controller->CastToPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	
	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Hit.GetActor()->GetName());
			if (Hit.GetActor()->GetName().Find("Landscape") != -1) {
				if (this->UnitySelected.Num()) {
					for (auto& Unity : this->UnitySelected) {
						Unity->GoTo(FVector(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z));
					}
				}
			}
		}
	}
}

void ARtsSpectatorPawn::UnselectAll()
{
	if (this->UnitySelected.Num()) {
		for (auto& Unity : this->UnitySelected) {
			Unity->Unselect();
		}
		this->UnitySelected.Empty();
	}
}