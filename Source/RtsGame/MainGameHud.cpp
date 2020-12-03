// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameHud.h"

#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Unity.h"


AMainGameHud::AMainGameHud() : Super()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainGameHud::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameHud::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AMainGameHud::DrawHUD()
{
	Super::DrawHUD();

	if (GEngine && GEngine->GameViewport)
	{
		FVector2D viewportSize;
		GEngine->GameViewport->GetViewportSize(viewportSize);
		this->UiScale = viewportSize.X / 2048.f;
	}

	DrawHealthBars();

	if (GetPlayerController()->GetIsSelectionActive())
	{
		const FVector selectionStartPosition = Canvas->Project(GetPlayerController()->GetSelectionStartPosition());

		DrawSelectionGrid(FVector2D(selectionStartPosition));
	}
	DrawRessourcesBars();
}

void AMainGameHud::DrawHealthBars() const
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AUnity::StaticClass(), FoundActors);
	// Get all pawns in the game
	for (auto *Actor : FoundActors)
	{
		// If the pawn is a ARTSBR_Character and is not death
		AUnity* Character = Cast<AUnity>(Actor);
		if (Character && Character->GetHealth() > 0)
		{
			// Select the center point of the bar as the character's location
			FVector Center = Character->GetActorLocation();
			
			// Offsets of the bar
			FVector extent = FVector(60.f, 34.f, 131.75f);

			// Project function of Canvas translates a world position to the screen position
			FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X, Center.Y, Center.Z + extent.Z)));

			float ActorExtent = 50.f;
			float HealthPercentage = 0.5f;
			float YOffset = 10.f;

			HealthPercentage = Character->GetHealth() / Character->GetMaxHealth();
			ActorExtent = Character->GetCapsuleComponent()->GetScaledCapsuleRadius();

			FVector Pos1 = Canvas->Project(FVector(Center.X, Center.Y - ActorExtent * 2, Center.Z + extent.Z));
			FVector Pos2 = Canvas->Project(FVector(Center.X, Center.Y + ActorExtent * 2, Center.Z + extent.Z));

			float BarWidth = (Pos2 - Pos1).Size2D();
			float BarHeight = BarWidth / 10;


			float x = Center2D.X - BarWidth * 0.5f;
			float y = Center2D.Y;

			x = Center2D.X - BarWidth * 0.5f;
			y = Center2D.Y - 1.f;
			FCanvasTileItem TileItem(FVector2D(x, y), FVector2D(BarWidth * HealthPercentage, BarHeight), FLinearColor(0.f, 1.0f, 0.f, 0.7f));
			TileItem.BlendMode = SE_BLEND_Translucent;


			Canvas->DrawItem(TileItem);
		}
	}
}

void AMainGameHud::DrawSelectionGrid(FVector2D GridStartPos)
{
	FVector2D MousePosition;
	GetPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y);

	float GridWidth = MousePosition.X - GridStartPos.X;
	float GridHeight = MousePosition.Y - GridStartPos.Y;

	FCanvasTileItem fillTileItem(GridStartPos, FVector2D(GridWidth, GridHeight), FLinearColor(1.0f, 1.0f, 1.0f, 0.2f));
	fillTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(fillTileItem);

	FCanvasTileItem TileItem(GridStartPos, FVector2D(GridWidth, 1.f), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(GridWidth * 0.1f, 1.f);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos + FVector2D(0.f, GridHeight);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos;
	TileItem.Size = FVector2D(1.f, GridHeight);
	TileItem.UV1 = FVector2D(1.f, GridHeight * 0.1f);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos + FVector2D(GridWidth, 0.f);
	Canvas->DrawItem(TileItem);
}

ARtsPlayerController *AMainGameHud::GetPlayerController() const
{
	return Cast<ARtsPlayerController>(PlayerOwner);
}

void AMainGameHud::DrawRessourcesBars()
{
	float GridWidth = GSystemResolution.ResX / 5;
	float GridHeight = GSystemResolution.ResY / 17;

	FCanvasTileItem fillTileItem(FVector2D(0.f, 0.f), FVector2D(GridWidth, GridHeight), FLinearColor(1.0f, 0.647f, 0.2f, 0.5f));
	fillTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(fillTileItem);

/*	FCanvasTileItem TileItem(GridStartPos, FVector2D(GridWidth, 1.f), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(GridWidth * 0.1f, 1.f);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos + FVector2D(0.f, GridHeight);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos;
	TileItem.Size = FVector2D(1.f, GridHeight);
	TileItem.UV1 = FVector2D(1.f, GridHeight * 0.1f);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos + FVector2D(GridWidth, 0.f);
	Canvas->DrawItem(TileItem);*/
}