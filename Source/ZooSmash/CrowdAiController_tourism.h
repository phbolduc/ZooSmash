// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CrowdAiController.h"
#include "CrowdAiController_tourism.generated.h"

/**
 * 
 */
UCLASS()
class ZOOSMASH_API ACrowdAiController_tourism: public ACrowdAiController
{
	GENERATED_BODY()

	protected:
		virtual void SecondPhase() override;
		virtual void SecondPhaseFail(EPathFollowingResult::Type moveResult) override;
};
