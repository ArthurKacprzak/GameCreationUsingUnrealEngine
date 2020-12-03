// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Animation/BlendSpace1D.h"
#include "Unity.generated.h"

UCLASS()
class RTSGAME_API AUnity : public ACharacter
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AUnity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
	UStaticMeshComponent* Selected;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Initialisation")
    float Speed = 900.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
	float MaxHealth = 100.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const float GetSpeed() const
	{
		return this->GetVelocity().Size();
	}

	float GetHealth() const
	{
		return this->Health;
	}

	float GetMaxHealth() const
	{
		return this->MaxHealth;
	}

public:
	void GoTo(FVector Position);

	void Select();

	void Unselect();

private:
	void InitAnimation();
	void InitCapsuleComponent();
};
