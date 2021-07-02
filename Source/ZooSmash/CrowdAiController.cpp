// Fill out your copyright notice in the Description page of Project Settings.

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

class UAIAsyncTaskBlueprintProxy;

void ACrowdAiController::FirstPhase() {
	APawn* listPawnAI{};
	FVector actorForwardVector(EForceInit::ForceInit);
	FVector location(EForceInit::ForceInit);
	FVector calcVector(EForceInit::ForceInit);
	FVector dest(EForceInit::ForceInit);
	bool hasPointInRadius{};
	FVector randomVector(EForceInit::ForceInit);
	FVector randomLocation(EForceInit::ForceInit);
	bool hasMultipleObjectInSphere = false;
	int32 len{};
	int32 randomInt{};
	int32 SubInt{};
	bool hasGetPoint{};
	TArray< FHitResult > sphereOutHit = TArray<FHitResult>();

	ChangeSpeedCharacter(250.0f);

	listPawnAI = AController::K2_GetPawn();
	if (::IsValid(listPawnAI) && ::IsValid(listPawnAI))
	{
		actorForwardVector = listPawnAI->AActor::GetActorForwardVector();
		location = listPawnAI->AActor::K2_GetActorLocation();

		calcVector = UKismetMathLibrary::Multiply_VectorFloat(actorForwardVector, 500.0f);
		calcVector = UKismetMathLibrary::Add_VectorVector(location, calcVector);
		// hasPointInRadius = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, calcVector, randomLocation, 10.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		randomLocation = FVector(0, 0, 0);

		randomVector = UKismetMathLibrary::RandomUnitVector();
		calcVector = UKismetMathLibrary::Multiply_VectorFloat(randomVector, 100.0f);
		calcVector = UKismetMathLibrary::Add_VectorVector(randomLocation, calcVector);

		TArray<TEnumAsByte<EObjectTypeQuery>> searchPoint = TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 });
		TArray<AActor*> ignorePoint = TArray<AActor*>({ currentDest });
		(sphereOutHit).Reset();
		hasMultipleObjectInSphere = UKismetSystemLibrary::SphereTraceMultiForObjects(this, randomLocation, calcVector, SearchRadius,
			searchPoint, false, ignorePoint, EDrawDebugTrace::ForDuration, /*out*/ sphereOutHit, true,
			FLinearColor(1.000000, 0.000000, 0.000000, 1.000000), FLinearColor(0.000000, 1.000000, 0.000000, 1.000000), 5.00);
	}

	if (!hasMultipleObjectInSphere)
	{
		SearchRadius = UKismetMathLibrary::Add_FloatFloat(SearchRadius, InitSearchRadius);
		FirstPhase();
	}
	else {
		SearchRadius = InitSearchRadius;
		len = FCustomThunkTemplates::Array_Length(sphereOutHit);
		randomInt = UKismetMathLibrary::RandomIntegerInRange(1, len) - 1;

		bool BlockingHit, bInitialOverlap;
		float hitTime, hitDistance;
		FVector hitLocation, impactPoint, hitNormal, hitNormalImpact, traceStart, traceEnd;
		FName hitBoneName;
		int32 faceIndex, hitItem;
		AActor* hitActor;
		UPhysicalMaterial* physMat;
		UPrimitiveComponent* hitComponent;

		UGameplayStatics::BreakHitResult(sphereOutHit[SubInt], BlockingHit, bInitialOverlap, hitTime, hitDistance, hitLocation, impactPoint, hitNormal,
			hitNormalImpact, physMat, hitActor, /*out*/ hitComponent, hitBoneName, hitItem, faceIndex, traceStart, traceEnd);
		currentDest = hitActor;
		// hasGetPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, impactPoint, dest, 10.000000, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		dest = FVector(0, 0, 0);

		WalkTo(dest);
	}
}

void ACrowdAiController::SecondPhase() {
    ACrowdAiController::FirstPhase();
}

void ACrowdAiController::SecondPhaseFail(EPathFollowingResult::Type moveResult) {
    ACrowdAiController::FirstPhaseFail(moveResult);
}

void ACrowdAiController::ChangeSpeedCharacter(float maxSpeed)
{
    APawn* pawnList = AController::K2_GetPawn();
    AZooSmashCharacter* nodeCharacter = Cast<AZooSmashCharacter>(pawnList);
    bool hasPawn = (nodeCharacter != nullptr);
    if (hasPawn && UKismetSystemLibrary::IsValid(nodeCharacter) 
		&& UKismetSystemLibrary::IsValid((*(AccessPrivateProperty<UCharacterMovementComponent* >((nodeCharacter), ACharacter::__PPO__CharacterMovement())))))
	{
		(*(AccessPrivateProperty<UCharacterMovementComponent* >((nodeCharacter), ACharacter::__PPO__CharacterMovement())))->MaxWalkSpeed = maxSpeed;
	}
}

void ACrowdAiController::WalkTo(FVector dest)
{
	WalkTo(dest, InitSearchRadius, FName(TEXT("MoveSuccess")), FName(TEXT("FirstPhaseFail")));
}

void ACrowdAiController::WalkTo(FVector dest, float rayon, FName successFunc, FName failFunc)
{
	UAIAsyncTaskBlueprintProxy* moveProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, ((APawn*)nullptr), dest, ((AActor*)nullptr), rayon, false);
	if (UKismetSystemLibrary::IsValid(moveProxy))
	{
		TScriptDelegate<FWeakObjectPtr> callSuccess, callFail;
		callSuccess.BindUFunction(this, successFunc);
		callFail.BindUFunction(this, failFunc);
		moveProxy->OnSuccess.AddUnique(callSuccess);
		moveProxy->OnFail.AddUnique(callFail);
	}
}


void ACrowdAiController::MoveSuccess(EPathFollowingResult::Type moveResult)
{
	APawn* playerPawn{};
	APawn* AiPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);
	float distance{};
	bool isLess{};

	playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = AController::K2_GetPawn();
	if (UKismetSystemLibrary::IsValid(playerPawn))
	{
		playerLocation = playerPawn->AActor::K2_GetActorLocation();
	}
	if (UKismetSystemLibrary::IsValid(AiPawn))
	{
		aiLocation = AiPawn->AActor::K2_GetActorLocation();
	}
	distance = UKismetMathLibrary::Vector_Distance(aiLocation, playerLocation);
	isLess = UKismetMathLibrary::Less_FloatFloat(distance, 4 * SearchRadius);
	if (!isLess)
	{
		FirstPhase();
	}
	else {
		SecondPhase();
	}
}

void ACrowdAiController::FirstPhaseFail(EPathFollowingResult::Type moveResult)
{
	APawn* playPawn{};
	APawn* aiPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);
	FVector randomLocation;
	float distance{};
	float rayon{};
	bool isSmaller{};
	bool hasRandomPoint{};

	playPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	aiPawn = AController::K2_GetPawn();
	if (UKismetSystemLibrary::IsValid(playPawn))
	{
		playerLocation = playPawn->AActor::K2_GetActorLocation();
	}
	if (UKismetSystemLibrary::IsValid(aiPawn))
	{
		aiLocation = aiPawn->AActor::K2_GetActorLocation();
	}
	distance = UKismetMathLibrary::Vector_Distance(aiLocation, playerLocation);
	rayon = 4 * SearchRadius;
	isSmaller = UKismetMathLibrary::Less_FloatFloat(distance, rayon);
	if (!isSmaller)
	{
		isSmaller = UKismetMathLibrary::Greater_FloatFloat(distance, rayon);
		if (isSmaller)
		{
			UKismetSystemLibrary::Delay(this, 0.200000, FLatentActionInfo(2, -41540233, TEXT("ExecuteUbergraph_crowdMainControler_0"), this));
		}
	}

	if(isSmaller) {
		// hasRandomPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, aiLocation, randomLocation, 100.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		randomLocation = FVector(0, 0, 0);
		
		WalkTo(randomLocation, 5.0f, FName(TEXT("SecondPhase")), FName(TEXT("SecondPhaseFail")));
	}
}

/**
 * Called when the game starts or when spawned
 */
void ACrowdAiController::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Start")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
	SearchRadius = InitSearchRadius;
	FirstPhase();
}