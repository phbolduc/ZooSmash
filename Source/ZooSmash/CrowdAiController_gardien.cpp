// Fill out your copyright notice in the Description page of Project Settings.

#include "CrowdAiController_gardien.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "CoreMinimal.h"

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
	FTimerHandle _loopTimerHandle = FTimerHandle();
	FTimerHandle _loopTimerHandle2 = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ACrowdAiController_gardien::Shoot, 2.4f, false);
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle2, this, &ACrowdAiController_gardien::MoveSuccess, 2.5f, false);
}

void ACrowdAiController_gardien::MoveSuccess()
{
	isSafe = Super::IsFarOfPlayer();
	Super::MoveSuccess();
}

void ACrowdAiController_gardien::Shoot() 
{
	ACharacter* characterAI = GetCharacter();
	try {
		AMyAICharacter* myCharacterAI = static_cast<AMyAICharacter*>(characterAI);
		if (myCharacterAI != nullptr) {
			myCharacterAI->OnShoot();
		}
	}
	catch (...) {
		UKismetSystemLibrary::PrintString(this, FString(characterAI->GetName()), true, true, FLinearColor(0, 0.66, 1.0, 1.0), 20);
	}
}

void ACrowdAiController_gardien::LookAt() 
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	APawn* AiPawn = GetPawn();

	FVector playerLocation(EForceInit::ForceInit);
	FVector aiLocation(EForceInit::ForceInit);
	FRotator aiRotation;

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{
		playerLocation = PlayerPawn->GetActorLocation();
		aiLocation = AiPawn->GetActorLocation();
		aiRotation = AiPawn->GetActorRotation();
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(playerLocation, aiLocation);

		rot.Pitch = 0;
		rot.Roll = 0;
		rot.Yaw += 180; 
		FHitResult* hitResult = nullptr;	
		AiPawn->AddActorWorldRotation((rot - aiRotation), false, hitResult, ETeleportType::None);
	}
}