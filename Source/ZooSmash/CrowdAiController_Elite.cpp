
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
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Elite !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);
	
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

	UKismetSystemLibrary::PrintString(this, FString(TEXT("Elite !!!")), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 2.000000);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AiPawn = AController::K2_GetPawn();

	if (::IsValid(PlayerPawn) && ::IsValid(AiPawn))
	{

		forwardPlayer = PlayerPawn->AActor::GetActorForwardVector();
		playerLocation = PlayerPawn->AActor::K2_GetActorLocation();
		
		aiLocation = AiPawn->AActor::K2_GetActorLocation();
		UKismetSystemLibrary::PrintString(this, FString(aiLocation.ToString()), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20);
		
		MoveVector = forwardPlayer.RotateAngleAxis(90.0f, FVector(0,0,1));
		MoveVector = UKismetMathLibrary::Normal(MoveVector, 0.000100);
		MoveVector = UKismetMathLibrary::Multiply_VectorFloat(MoveVector, 2 * SearchRadius);
		destA = aiLocation - MoveVector;
		destB = aiLocation + MoveVector;
		
		if(FVector::Distance(destA, playerLocation) < FVector::Distance(destB, playerLocation))
		{
			MoveVector = destB;
		} 
		else
		{
			MoveVector = destA;
		}
		
		UKismetSystemLibrary::PrintString(this, FString(MoveVector.ToString()), true, true, FLinearColor(0.000000, 0.660000, 1.000000, 1.000000), 20);

		ChangeSpeedCharacter(500.0f);
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, MoveVector, dest, 1.000000, ((ANavigationData*)nullptr), ((UClass*)nullptr));
		Super::WalkTo(dest);
		//  X=1000.000 Y=5548.058 Z=41.818 à X=1000.000 Y=5783.094 Z=53.605

		// X=1023.017 Y=4957.667 Z=90.050 à X=1030.714 Y=4951.282 Z=90.050
	}
	else {
		Super::MoveSuccess();
	}
}