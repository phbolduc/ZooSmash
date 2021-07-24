
#include "CrowdAiController_Elite.h"

#include "ZooSmash/ZooSmashCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/EngineTypes.h"
#include "UObject/Object.h"
#include "UObject/NameTypes.h"

#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationData.h"

#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"

#include "AIController.h"
#include "CrowdAiController.h"
#include "CrowdAiController_gardien.h"

void ACrowdAiController_Elite::SecondPhase()
{
	FTimerHandle _loopTimerHandle;

	Super::LookAt();
	Super::Shoot();

	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ACrowdAiController_Elite::MoveAfterShoot, 0.1f, false);
}

void ACrowdAiController_Elite::MoveAfterShoot()
{
	APawn* PlayerPawn{};
	FVector forwardPlayer(EForceInit::ForceInit);
	FVector playerLocation(EForceInit::ForceInit);

	APawn* AiPawn{};
	FVector aiLocation(EForceInit::ForceInit);

	FVector dest;
	FVector destA;
	FVector destB;
	FVector MoveVector(EForceInit::ForceInit);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = GetPawn();

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{

		forwardPlayer = PlayerPawn->GetActorForwardVector();
		playerLocation = PlayerPawn->GetActorLocation();
		
		aiLocation = AiPawn->GetActorLocation();

		MoveVector = forwardPlayer.RotateAngleAxis(90.0f, FVector(0,0,1));
		MoveVector = UKismetMathLibrary::Normal(MoveVector, 0.000100);
		MoveVector = UKismetMathLibrary::Multiply_VectorFloat(MoveVector, 2 * SearchRadius);
		destA = UKismetMathLibrary::Add_VectorVector(aiLocation, -MoveVector);
		destB = UKismetMathLibrary::Add_VectorVector(aiLocation, MoveVector);
		
		if(FVector::Distance(destA, playerLocation) < FVector::Distance(destB, playerLocation))
		{
			MoveVector = destB;
		} 
		else
		{
			MoveVector = destA;
		}

		ChangeSpeedCharacter(400.0f);
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, MoveVector, dest, 1.0, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		WalkTo(dest);
	}
	else {
		Super::MoveSuccess();
	}
}