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

class UAIAsyncTaskBlueprintProxy;

#include "CrowdAiController.generated.h"


/**
 * 
 */
UCLASS()
class ZOOSMASH_API ACrowdAiController : public AAIController
{
	GENERATED_BODY()
		
	protected:
		UPROPERTY(BlueprintReadWrite, Category = "ACrowdAiController_old")
			float defaultSpeed = 250.0f;
		UPROPERTY(BlueprintReadWrite, Category = "ACrowdAiController_old")
			float InitSearchRadius = 300.0f;
		float SearchRadius = 200.0f;
		AActor* currentDest = nullptr;

		virtual void BeginPlay() override;

		virtual void FirstPhase();
		virtual void FirstPhaseFail(EPathFollowingResult::Type moveResult);

		virtual void SecondPhase();
		virtual void SecondPhaseFail(EPathFollowingResult::Type moveResult);

		virtual void WalkTo(FVector dest);
		virtual void WalkTo(FVector dest, float rayon, FName successFunc, FName failFunc);

		virtual void MoveSuccess(EPathFollowingResult::Type moveResult);
		virtual void MoveSuccess();

		virtual void ChangeSpeedCharacter(float maxSpeed);
		virtual bool IsFarOfPlayer();
};
