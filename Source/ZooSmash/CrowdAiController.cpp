// Fill out your copyright notice in the Description page of Project Settings.

#include "CrowdAiController.h"

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
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"

#include "AIController.h"

class UAIAsyncTaskBlueprintProxy;
class UNavigationSystemV1;
class UNavigationQueryFilter;
class ANavigationData;
template<class TClass>
class TSubclassOf;

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
	bool hasGetPoint{};
	TArray< FHitResult > sphereOutHit = TArray<FHitResult>();

	ChangeSpeedCharacter(defaultSpeed);

	listPawnAI = GetPawn();
	if (::IsValid(listPawnAI) && ::IsValid(listPawnAI))
	{
		randomInt = UKismetMathLibrary::RandomIntegerInRange(0, 3);
		actorForwardVector = listPawnAI->GetActorForwardVector();
		location = listPawnAI->GetActorLocation();

		if (randomInt > 1){
			actorForwardVector = actorForwardVector.RotateAngleAxis(90.0f, FVector(0, 0, 1));
			actorForwardVector = (randomInt == 2) ? location + actorForwardVector : location - actorForwardVector;
		}

		calcVector = UKismetMathLibrary::Multiply_VectorFloat(actorForwardVector, 500.0f);
		calcVector = UKismetMathLibrary::Add_VectorVector(location, calcVector);
		hasPointInRadius = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, calcVector, randomLocation, 10.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));

		randomVector = UKismetMathLibrary::RandomUnitVector();
		calcVector = UKismetMathLibrary::Multiply_VectorFloat(randomVector, 100.0f);
		calcVector = UKismetMathLibrary::Add_VectorVector(randomLocation, calcVector);

		TArray<TEnumAsByte<EObjectTypeQuery>> searchPoint = TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 });
		TArray<AActor*> ignorePoint = TArray<AActor*>({ currentDest });
		(sphereOutHit).Reset();
		hasMultipleObjectInSphere = UKismetSystemLibrary::SphereTraceMultiForObjects(this, randomLocation, calcVector, SearchRadius,
			searchPoint, false, ignorePoint, EDrawDebugTrace::None, /*out*/ sphereOutHit, true,
			FLinearColor(0.0, 0.0, 0.0, 0.0), FLinearColor(0.0, 0.0, 0.0, 0.0), 0.0);
	}

	if (!hasMultipleObjectInSphere)
	{
		SearchRadius = UKismetMathLibrary::Add_FloatFloat(SearchRadius, InitSearchRadius);
		if (SearchRadius <= InitSearchRadius * 4) {
			FirstPhase();
		}
		else
		{
			SearchRadius = InitSearchRadius;
			MoveSuccess();
		}
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

		// Get the hitActor
		UGameplayStatics::BreakHitResult(sphereOutHit[randomInt], BlockingHit, bInitialOverlap, hitTime, hitDistance, hitLocation, impactPoint, hitNormal,
			hitNormalImpact, physMat, hitActor, /*out*/ hitComponent, hitBoneName, hitItem, faceIndex, traceStart, traceEnd);
		currentDest = hitActor;

		// Get a position around the hit actor
		hasGetPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, impactPoint, dest, 10.000000, ((ANavigationData*)nullptr), ((UClass*)nullptr));

		WalkTo(dest);
	}
}

void ACrowdAiController::SecondPhase()
{
	ACrowdAiController::FirstPhase();
}

void ACrowdAiController::ChangeSpeedCharacter(float maxSpeed)
{
    APawn* pawnList = GetPawn();
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
	WalkTo(dest, InitSearchRadius, 5.0f);
}
void ACrowdAiController::WalkTo(FVector dest, float rayon, float timeToWait)
{
	UAIAsyncTaskBlueprintProxy* moveProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, ((APawn*)nullptr), dest, ((AActor*)nullptr), rayon, false);
	FTimerHandle _loopTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ACrowdAiController::MoveSuccess, timeToWait, false);
}

void ACrowdAiController::MoveSuccess()
{
	mustReact = true;
}


bool ACrowdAiController::IsFarOfPlayer()
{
	APawn* playPawn{};
	APawn* aiPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);
	bool isSmaller = true;
	bool hasRandomPoint{};
	float distance{};

	playPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	aiPawn = GetPawn();

	if (UKismetSystemLibrary::IsValid(playPawn) && UKismetSystemLibrary::IsValid(aiPawn))
	{
		playerLocation = playPawn->GetActorLocation();
		aiLocation = aiPawn->GetActorLocation();
		distance = UKismetMathLibrary::Vector_Distance(aiLocation, playerLocation);
		isSmaller = UKismetMathLibrary::Less_FloatFloat(InitSearchRadius * 3, distance);
	}

	return  !canSwitchPhase || isSmaller;
}

/**
 * Called when the game starts or when spawned
 */
void ACrowdAiController::BeginPlay()
{
	Super::BeginPlay();

	//UKismetSystemLibrary::PrintString(this, FString(TEXT("Start")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
	SearchRadius = InitSearchRadius;
	MoveSuccess();
}

void ACrowdAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (mustReact) {
		mustReact = false;
		isFirstPhase = IsFarOfPlayer();
		if (isFirstPhase)
		{
			this->FirstPhase();
		}
		else {
			this->SecondPhase();
		}
	}

}