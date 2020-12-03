// Fill out your copyright notice in the Description page of Project Settings.


#include "Unity.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "RtsAnimInstance.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationPath.h"

// Sets default values
AUnity::AUnity() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->InitCapsuleComponent();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> characterSkeletalMeshAsset(TEXT("SkeletalMesh'/Game/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash'"));
	if (characterSkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(characterSkeletalMeshAsset.Object);

		this->InitAnimation();
	}
	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));


	GetMesh()->SetupAttachment(this->RootComponent);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -120.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));



	this->Selected = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSelected"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SelectedVisualAsset(TEXT("StaticMesh'/Game/RtsGame/Map/Shape/Shape_Torus.Shape_Torus'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface> Material_Gold(TEXT("Material'/Game/RtsGame/Map/Materials/M_Ground_Grass.M_Ground_Grass'"));

	if (SelectedVisualAsset.Succeeded() && Material_Gold.Succeeded())
	{
		this->Selected->SetStaticMesh(SelectedVisualAsset.Object);
		this->Selected->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		this->Selected->SetRelativeScale3D(FVector(0.f, 0.f, 0.f));
		this->Selected->SetMaterial(0, Material_Gold.Object);
	}
	
//	this->Selected->SetupAttachment(this->RootComponent);
}

void AUnity::InitAnimation()
{
	static ConstructorHelpers::FClassFinder<URtsAnimInstance> animationBlueprintClass(TEXT("AnimBlueprint'/Game/RtsGame/HeroOrc/Basic/UnityAnimBP.UnityAnimBP_C'"));

	this->GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	if (animationBlueprintClass.Class) {
		this->GetMesh()->SetAnimInstanceClass(animationBlueprintClass.Class);
	}
}

void AUnity::InitCapsuleComponent()
{
	this->GetCapsuleComponent()->InitCapsuleSize(70, 150);
	this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void AUnity::BeginPlay()
{
	Super::BeginPlay();
	
	this->Selected->SetVisibility(false);
}

// Called every frame
void AUnity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnity::GoTo(FVector Position)
{
	FVector Location = GetActorLocation();
	UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* path = navSys->FindPathToLocationSynchronously(GetWorld(), Location, Position, this);

	if (path && path->IsValid())
	{
		FAIMoveRequest req;
		req.SetAcceptanceRadius(50);
		req.SetUsePathfinding(true);

		AAIController* ai = Cast<AAIController>(this->GetController());
		if (ai) {
			this->GetCharacterMovement()->MaxWalkSpeed = this->Speed;
			ai->RequestMove(req, path->GetPath());
		}
	}
}

void AUnity::Select()
{
	this->Selected->SetVisibility(true);
}

void AUnity::Unselect()
{
	this->Selected->SetVisibility(false);
}