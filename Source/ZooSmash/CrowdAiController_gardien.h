// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"

#include "CrowdAiController.h"
#include "CrowdAiController_gardien.generated.h"

/**
 * 
 */
UCLASS()
class ZOOSMASH_API ACrowdAiController_gardien : public ACrowdAiController
{
	GENERATED_BODY()

	protected:
		bool isSafe = true;
		
		virtual void Tick(float DeltaSeconds) override;
		virtual void MoveSuccess() override;

		virtual void SecondPhase() override;

		virtual void Shoot();
		virtual void LookAt();
};
