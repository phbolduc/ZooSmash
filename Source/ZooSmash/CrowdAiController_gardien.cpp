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
#include "MyAICharacter.h"


void ACrowdAiController_gardien::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
	if (!isSafe) {
		LookAt();
	}
}

void ACrowdAiController_gardien::SecondPhase()
{	
	FTimerHandle _loopTimerHandle;
	FTimerHandle _loopTimerHandle2;
	//GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ACrowdAiController_gardien::Shoot, 4.9f, false);
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle2, this, &ACrowdAiController_gardien::MoveSuccess, 5.0f, false);
}

void ACrowdAiController_gardien::MoveSuccess()
{
	isSafe = Super::IsFarOfPlayer();
	Super::MoveSuccess();
}

void ACrowdAiController_gardien::SecondPhaseFail(EPathFollowingResult::Type moveResult)
{
	ACrowdAiController_gardien::MoveSuccess();
}

void ACrowdAiController_gardien::WalkTo(FVector dest)
{
	Super::WalkTo(dest);
}

void ACrowdAiController_gardien::Shoot() 
{
	ACharacter* characterAI = AController::GetCharacter();
	//(static_cast<AMyAICharacter*>(characterAI))->OnShoot();
	//UKismetSystemLibrary::PrintString(this, FString(TEXT("Shoot !!!")), true, true, FLinearColor(0.0, 0.66, 1.0, 1.0), 2.0);
}

void ACrowdAiController_gardien::LookAt() 
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	APawn* AiPawn = AController::K2_GetPawn();
	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);
	FRotator aiRotation;

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{
		playerLocation = PlayerPawn->AActor::K2_GetActorLocation();
		aiLocation = AiPawn->AActor::K2_GetActorLocation();
		aiRotation = AiPawn->AActor::GetActorRotation();
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(playerLocation, aiLocation);
		rot.Pitch = 0;
		rot.Roll = 0;
		rot.Yaw += 180; 
		FHitResult hitResult;	
		AiPawn->AActor::K2_AddActorWorldRotation((rot - aiRotation), false, hitResult, false);
		
	}
}