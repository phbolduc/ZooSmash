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
	int32 SubInt{};
	bool hasGetPoint{};
	TArray< FHitResult > sphereOutHit = TArray<FHitResult>();
	

	UKismetSystemLibrary::PrintString(this, FString(TEXT("First phase")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20);

	ChangeSpeedCharacter(defaultSpeed);

	listPawnAI = AController::K2_GetPawn();
	if (::IsValid(listPawnAI) && ::IsValid(listPawnAI))
	{
		actorForwardVector = listPawnAI->AActor::GetActorForwardVector();
		location = listPawnAI->AActor::K2_GetActorLocation();

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
		hasGetPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, impactPoint, dest, 10.000000, ((ANavigationData*)nullptr), ((UClass*)nullptr));

		WalkTo(dest);
	}
}

void ACrowdAiController::SecondPhase() {

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Second phase")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20);
    ACrowdAiController::FirstPhase();
}

void ACrowdAiController::SecondPhaseFail(EPathFollowingResult::Type moveResult) {

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Fail 2 phase")), true, true, FLinearColor(0.0, 0.66, 1.00, 1.00), 20.0);
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

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Walk to")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20.00);
	UAIAsyncTaskBlueprintProxy* moveProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this, ((APawn*)nullptr), dest, ((AActor*)nullptr), rayon, false);

	return; //KCST_EndOfThread

	if (UKismetSystemLibrary::IsValid(moveProxy))
	{
		FString textToPrint = FString(TEXT("id : "));
		textToPrint.AppendInt(moveProxy->MoveRequestId.GetID());
		UKismetSystemLibrary::PrintString(this, textToPrint, true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20.0);

		TScriptDelegate<FWeakObjectPtr> callSuccess, callFail;
		callSuccess.BindUFunction(this, successFunc);

		callFail.BindUFunction(this, failFunc);

		moveProxy->OnSuccess.AddUnique(callSuccess);
		moveProxy->OnFail.AddUnique(callFail);

		// Ligne temporaire PATCH;
		GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle2, this, &ACrowdAiController::MoveSuccess, 0.10f, false);
		//moveProxy->OnSuccess.AddDynamic(this, &ACrowdAiController::MoveSuccess);
		//moveProxy->OnFail.AddDynamic(this, &ACrowdAiController::FirstPhaseFail);
		//MoveSuccess();
	}
	else {
		UKismetSystemLibrary::PrintString(this, FString(TEXT("Fail Walk to !!!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20.0);
		MoveSuccess();
	}
}

void ACrowdAiController::MoveSuccess(EPathFollowingResult::Type moveResult)
{
	MoveSuccess();
}

void ACrowdAiController::MoveSuccess()
{
	UKismetSystemLibrary::PrintString(this, FString(TEXT("MoveSuccess!!!!")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 20.00);
	if (IsFarOfPlayer())
	{
		this->FirstPhase();
	}
	else {
		this->SecondPhase();
	}
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
	aiPawn = AController::K2_GetPawn();
	if (!UKismetSystemLibrary::IsValid(playPawn) || !UKismetSystemLibrary::IsValid(aiPawn))
	{
		UKismetSystemLibrary::PrintString(this, FString(TEXT("Error componant")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
		UKismetSystemLibrary::Delay(this, 0.200000, FLatentActionInfo(2, -41540233, TEXT("MoveSuccess"), this));
	}

	playerLocation = playPawn->AActor::K2_GetActorLocation();
	aiLocation = aiPawn->AActor::K2_GetActorLocation();
	
	if (IsFarOfPlayer())
	{
		UKismetSystemLibrary::Delay(this, 0.200000, FLatentActionInfo(2, -41540233, TEXT("MoveSuccess"), this));
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
	float distance{};
	float rayon{};
	bool isSmaller = true;
	bool hasRandomPoint{};

	playPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	aiPawn = AController::K2_GetPawn();

	if (UKismetSystemLibrary::IsValid(playPawn) && UKismetSystemLibrary::IsValid(aiPawn))
	{
		playerLocation = playPawn->AActor::K2_GetActorLocation();
		aiLocation = aiPawn->AActor::K2_GetActorLocation();
		distance = UKismetMathLibrary::Vector_Distance(aiLocation, playerLocation);
		rayon = 4 * SearchRadius;
		isSmaller = UKismetMathLibrary::Less_FloatFloat(rayon, distance);

		if (isSmaller) {
			UKismetSystemLibrary::PrintString(this, FString(TEXT("isSmaller")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20.0);
		} 
		else {
			UKismetSystemLibrary::PrintString(this, FString(TEXT("isBig")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20.0);
		}
	}

	return isSmaller;
}

/**
 * Called when the game starts or when spawned
 */
void ACrowdAiController::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Start")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
	SearchRadius = InitSearchRadius;
	MoveSuccess();
}
