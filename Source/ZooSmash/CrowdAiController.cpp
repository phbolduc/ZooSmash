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

/*
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
	TArray<AActor*> sphereOutHit = TArray<AActor*>();
	

	// UKismetSystemLibrary::PrintString(this, FString(TEXT("First phase")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20);

	ChangeSpeedCharacter(defaultSpeed);

	listPawnAI = GetPawn();
	if (::IsValid(listPawnAI))
	{
		actorForwardVector = listPawnAI->GetActorForwardVector();
		randomInt = UKismetMathLibrary::RandomIntegerInRange(0, 3);

		if (randomInt <= 1) {
			calcVector = actorForwardVector;// UKismetMathLibrary::Multiply_VectorFloat(actorForwardVector, 1.1f);
		}
		else {
			location = listPawnAI->GetActorLocation();
			calcVector = actorForwardVector.RotateAngleAxis(90.0f, FVector(0, 0, 1));
			calcVector = UKismetMathLibrary::Normal(calcVector, 0.0100);

			if (randomInt == 2)
			{
				calcVector = location + calcVector;
			}
			else
			{
				calcVector = location - calcVector;
			}
		}

		TArray<TEnumAsByte<EObjectTypeQuery>> searchPoint = TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 });
		TArray<AActor*> ignorePoint = TArray<AActor*>({ currentDest });
		hasMultipleObjectInSphere = UKismetSystemLibrary::SphereOverlapActors(this, calcVector, SearchRadius/4, searchPoint, false, ignorePoint, sphereOutHit);
	}

	if (!hasMultipleObjectInSphere)
	{
		SearchRadius = UKismetMathLibrary::Add_FloatFloat(SearchRadius, InitSearchRadius); 
		FTimerHandle _loopTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ACrowdAiController::MoveSuccess, 0.1f, false);
	}
	else {
		SearchRadius = InitSearchRadius;
		len = FCustomThunkTemplates::Array_Length(sphereOutHit);
		randomInt = UKismetMathLibrary::RandomIntegerInRange(1, len) - 1;
		currentDest = sphereOutHit[randomInt];

		dest = sphereOutHit[randomInt]->GetActorLocation();
		randomVector = UKismetMathLibrary::RandomUnitVector();
		calcVector = UKismetMathLibrary::Multiply_VectorFloat(randomVector, 100.0f);
		dest = UKismetMathLibrary::Add_VectorVector(dest, calcVector);

		WalkTo(dest);
	}
}
*/

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

void ACrowdAiController::SecondPhase() {

	// UKismetSystemLibrary::PrintString(this, FString(TEXT("Second phase")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20);
    ACrowdAiController::FirstPhase();
}

void ACrowdAiController::SecondPhaseFail(EPathFollowingResult::Type moveResult) {

	// UKismetSystemLibrary::PrintString(this, FString(TEXT("Fail 2 phase")), true, true, FLinearColor(0.0, 0.66, 1.00, 1.00), 20.0);
    ACrowdAiController::FirstPhaseFail(moveResult);
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
	WalkTo(dest, InitSearchRadius, FName(TEXT("MoveSuccess")), FName(TEXT("FirstPhaseFail")));
}

void ACrowdAiController::WalkTo(FVector dest, float rayon, FName successFunc, FName failFunc)
{
	UAIAsyncTaskBlueprintProxy* moveProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, ((APawn*)nullptr), dest, ((AActor*)nullptr), rayon, false);
	FTimerHandle _loopTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ACrowdAiController::MoveSuccess, 0.5f, false);
	/*	
	if (UKismetSystemLibrary::IsValid(moveProxy))
	{
		TScriptDelegate<FWeakObjectPtr> callSuccess, callFail;
		callSuccess.BindUFunction(this, successFunc);
		callFail.BindUFunction(this, failFunc);

		moveProxy->OnSuccess.AddUnique(callSuccess);
		moveProxy->OnFail.AddUnique(callFail);
		moveProxy->OnSuccess.AddDynamic(this, &ACrowdAiController::MoveSuccess);
		moveProxy->OnFail.AddDynamic(this, &ACrowdAiController::FirstPhaseFail);
	}
	else {
		// Fail methode...
	}
	*/
}

void ACrowdAiController::MoveSuccess(EPathFollowingResult::Type moveResult)
{
	MoveSuccess();
}

void ACrowdAiController::MoveSuccess()
{
	mustReact = true;
}

void ACrowdAiController::FirstPhaseFail(EPathFollowingResult::Type moveResult)
{
	APawn* playPawn{};
	APawn* aiPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);
	FVector randomLocation;
	bool hasRandomPoint{};

	playPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	aiPawn = GetPawn();
	if (!UKismetSystemLibrary::IsValid(playPawn) || !UKismetSystemLibrary::IsValid(aiPawn))
	{
		// UKismetSystemLibrary::PrintString(this, FString(TEXT("Error componant")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
		UKismetSystemLibrary::Delay(this, 0.200000, FLatentActionInfo(2, -41540233, TEXT("MoveSuccess"), this));
	}

	playerLocation = playPawn->AActor::GetActorLocation();
	aiLocation = aiPawn->AActor::GetActorLocation();
	
	if (IsFarOfPlayer())
	{
		UKismetSystemLibrary::Delay(this, 0.2, FLatentActionInfo(2, -41540233, TEXT("MoveSuccess"), this));
	} 
	else 
	{
		hasRandomPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, aiLocation, randomLocation, 100.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		WalkTo(randomLocation, 5.0f, FName(TEXT("SecondPhase")), FName(TEXT("SecondPhaseFail")));
	}

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

	return isSmaller;
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