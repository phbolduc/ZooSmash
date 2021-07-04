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


void ACrowdAiController_gardien::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (!Super::IsFarOfPlayer()) {
		LookAt();
	}
}

void ACrowdAiController_gardien::SecondPhase()
{	
	UKismetSystemLibrary::PrintString(this, FString(TEXT("prep to shoot")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
	UKismetSystemLibrary::Delay(this, 0.200000, FLatentActionInfo(2, -41540233, TEXT("Shoot"), this));
	UKismetSystemLibrary::PrintString(this, FString(TEXT("has shoot")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
}

void ACrowdAiController_gardien::SecondPhaseFail(EPathFollowingResult::Type moveResult)
{
	Super::MoveSuccess();
}

void ACrowdAiController_gardien::Shoot() {
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Shoot !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
}

void ACrowdAiController_gardien::LookAt() {

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	APawn* AiPawn = AController::K2_GetPawn();
	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{
		playerLocation = PlayerPawn->AActor::K2_GetActorLocation();
		aiLocation = AiPawn->AActor::K2_GetActorLocation();
		UKismetMathLibrary::FindLookAtRotation(playerLocation, aiLocation);
	}
}