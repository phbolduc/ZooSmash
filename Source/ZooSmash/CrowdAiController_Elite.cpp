
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

	APawn* AiPawn{};
	FVector aiLocation(EForceInit::ForceInit);

	FVector dest;
	FVector MoveVector(EForceInit::ForceInit);

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Elite !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = AController::K2_GetPawn();

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{
		isSafe = Super::IsFarOfPlayer();
		Super::Shoot();
		isSafe = true;

		forwardPlayer = PlayerPawn->AActor::GetActorForwardVector();
		aiLocation = AiPawn->AActor::K2_GetActorLocation();
		MoveVector = forwardPlayer.RotateVector(90.0f, FVector(0,1,0));
		dest = UKismetMathLibrary::Add_VectorVector(aiLocation, MoveVector * 5);

		Super::WalkTo(dest);
	}
	else {
		Super::MoveSuccess();
	}
}
