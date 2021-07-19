// Fill out your copyright notice in the Description page of Project Settings.

#include "CrowdAiController_tourism.h"

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

void ACrowdAiController_tourism::SecondPhase()
{
	APawn* PlayerPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	APawn* AiPawn{};
	FVector AiLocation(EForceInit::ForceInit);
	FVector NewDir(EForceInit::ForceInit);
	FVector dest;
	FVector MoveVector(EForceInit::ForceInit);
	bool hasPoint{};

	//UKismetSystemLibrary::PrintString(this, FString(TEXT("Fear !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);

	ChangeSpeedCharacter(500.0f);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = GetPawn();

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{ 
		playerLocation = PlayerPawn->AActor::K2_GetActorLocation();
		AiLocation = AiPawn->AActor::K2_GetActorLocation();

		NewDir = UKismetMathLibrary::Subtract_VectorVector(AiLocation, playerLocation);
		NewDir = UKismetMathLibrary::Normal(NewDir, 0.000100);

		MoveVector = UKismetMathLibrary::Multiply_VectorFloat(NewDir, 2 * SearchRadius);
		MoveVector = UKismetMathLibrary::Add_VectorVector(AiLocation, MoveVector);
		hasPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, MoveVector, dest, 1.000000, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		
		dest.Z = AiLocation.Z;
		Super::WalkTo(dest);
	}
	else {
		Super::MoveSuccess();
	}

}

void ACrowdAiController_tourism::SecondPhaseFail(EPathFollowingResult::Type moveResult)
{
	APawn* aiPawn{};
	FVector aiLocotion(EForceInit::ForceInit);
	FVector randomPoint;
	bool hasRandomPoint{};
	FVector reverseDir(EForceInit::ForceInit);
	aiPawn = GetPawn();
	if (UKismetSystemLibrary::IsValid(aiPawn))
	{
		aiLocotion = aiPawn->AActor::K2_GetActorLocation();
		hasRandomPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, aiLocotion, randomPoint, 100.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		reverseDir = randomPoint * -1;
		Super::WalkTo(reverseDir, 5.0f, FName(TEXT("SecondPhase")), FName(TEXT("SecondPhase")));
	}
	else {
		Super::MoveSuccess();
	}
}
