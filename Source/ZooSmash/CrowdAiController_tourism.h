// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ZooSmash.h"
#include "ZooSmash/ZooSmashCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/CoreMiscDefines.h"

#include "Engine/EngineTypes.h"
#include "UObject/Object.h"
#include "UObject/NameTypes.h"
#include "Math/Color.h"

#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemConfig.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationData.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"

#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/AIModule/Classes/Blueprint/AIAsyncTaskBlueprintProxy.h"

#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"

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
