// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"

#include "AIController.h"
#include "CrowdAiController.generated.h"


/**
 * 
 */
UCLASS()
class ZOOSMASH_API ACrowdAiController : public AAIController
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(BlueprintReadWrite, Category = "Custom IA")
			bool isFirstPhase = true;
		UPROPERTY(BlueprintReadWrite, Category = "Custom IA")
			bool canSwitchPhase = false;

	protected:
		UPROPERTY(BlueprintReadWrite, Category = "Custom IA")
			float defaultSpeed = 250.0f;
		UPROPERTY(BlueprintReadWrite, Category = "Custom IA")
			float InitSearchRadius = 300.0f;

		bool mustReact = true;
		float SearchRadius = 200.0f;
		AActor* currentDest = nullptr;

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaSeconds) override;

		virtual void FirstPhase();

		virtual void SecondPhase();

		virtual void WalkTo(FVector dest);
		virtual void WalkTo(FVector dest, float rayon, float timeToWait);

		virtual void MoveSuccess();

		virtual void ChangeSpeedCharacter(float maxSpeed);
		virtual bool IsFarOfPlayer();
};
