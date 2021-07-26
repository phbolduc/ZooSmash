// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"

#include "CrowdAiController_gardien.h"
#include "CrowdAiController_Elite.generated.h"

/**
 * 
 */
UCLASS()
class ZOOSMASH_API ACrowdAiController_Elite : public ACrowdAiController_gardien
{
	GENERATED_BODY()

	protected:
		virtual void SecondPhase() override;
		virtual void MoveAfterShoot();
};
