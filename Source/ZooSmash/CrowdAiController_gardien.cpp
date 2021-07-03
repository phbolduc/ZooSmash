// Fill out your copyright notice in the Description page of Project Settings.

#include "CrowdAiController_gardien.h"

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


void ACrowdAiController_gardien::SecondPhase()
{
	APawn* PlayerPawn{};
	FVector location(EForceInit::ForceInit);
	APawn* AiPawn{};
	FVector AiLocation(EForceInit::ForceInit);
	FVector NewDir(EForceInit::ForceInit);
	FVector dest;
	float searchEffect{};
	FVector MoveVector(EForceInit::ForceInit);
	bool hasPoint{};

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Fear !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (::IsValid(PlayerPawn))
	{
		location = PlayerPawn->AActor::K2_GetActorLocation();
	}

	AiPawn = AController::K2_GetPawn();

	if (::IsValid(AiPawn))
	{
		AiLocation = AiPawn->AActor::K2_GetActorLocation();
	}
}

void ACrowdAiController_gardien::SecondPhaseFail(EPathFollowingResult::Type moveResult)
{
	if (Super::IsFarOfPlayer())
	{
		SecondPhase();
	}
	else {
		SecondPhase();
	}
}

// void ACrowdAiController_gardien::Shoot()
// void ACrowdAiController_gardien::lookAt()