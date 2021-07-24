// Fill out your copyright notice in the Description page of Project Settings.

#include "CrowdAiController_tourism.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationData.h"

#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"

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

	ChangeSpeedCharacter(500.0f);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = GetPawn();

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{
		playerLocation = PlayerPawn->K2_GetActorLocation();
		AiLocation = AiPawn->K2_GetActorLocation();

		NewDir = UKismetMathLibrary::Subtract_VectorVector(AiLocation, playerLocation);
		NewDir = UKismetMathLibrary::Normal(NewDir, 0.000100);
		MoveVector = UKismetMathLibrary::Multiply_VectorFloat(NewDir, 2 * SearchRadius);
		MoveVector = UKismetMathLibrary::Add_VectorVector(AiLocation, MoveVector);
		hasPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, MoveVector, dest, 1.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		
		WalkTo(dest);
	}
	else {
		MoveSuccess();
	}

}

void ACrowdAiController_tourism::SecondPhaseFail(EPathFollowingResult::Type moveResult)
{
	APawn* aiPawn{};
	FVector aiLocotion(EForceInit::ForceInit);
	FVector reverseDir(EForceInit::ForceInit);
	aiPawn = GetPawn();
	FVector randomPoint;
	bool hasRandomPoint{};

	if (UKismetSystemLibrary::IsValid(aiPawn))
	{
		aiLocotion = aiPawn->GetActorLocation();
		hasRandomPoint = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, aiLocotion, randomPoint, 100.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		reverseDir = randomPoint * -1;
		WalkTo(reverseDir, 5.0f, FName(TEXT("SecondPhase")), FName(TEXT("SecondPhase")));
	}
	else {
		MoveSuccess();
	}
}
