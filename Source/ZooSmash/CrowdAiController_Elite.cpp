
#include "CrowdAiController_Elite.h"

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
#include "CrowdAiController_gardien.h"



void ACrowdAiController_Elite::SecondPhase()
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

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Elite !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = AController::K2_GetPawn();

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{
		Super::isSafe = false;
		Super::Shoot();
		Super::isSafe = true;

		forwardPlayer = PlayerPawn->AActor::GetActorForwardVector();
		playerLocation = PlayerPawn->AActor::K2_GetActorLocation();
		
		aiLocation = AiPawn->AActor::K2_GetActorLocation();
	UKismetSystemLibrary::PrintString(this, FString(MoveVector.ToString()), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20);
		MoveVector = forwardPlayer.RotateAngleAxis(90.0f, FVector(0,0,1));
	UKismetSystemLibrary::PrintString(this, FString(MoveVector.ToString()), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20);
		destA = aiLocation + MoveVector * -10;
		destB = aiLocation + MoveVector * 10;
		
		if(FVector::Distance(destA, playerLocation) < FVector::Distance(destB, playerLocation))
		{
			dest = destB;
		} 
		else
		{
			dest = destA;
		}
		
		UKismetSystemLibrary::PrintString(this, FString(dest.ToString()), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20);

		Super::WalkTo(dest);
	}
	else {
		Super::MoveSuccess();
	}
}
