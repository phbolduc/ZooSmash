// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAI.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationData.h"

#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "GeneratedCodeHelpers.h"


class UAIAsyncTaskBlueprintProxy;
class UNavigationSystemV1;
class UNavigationQueryFilter;
class ANavigationData;

static float spawnRayon = 3000.0f;

static int numberSpawnTourism = 1; //10;
static int numberSpawnOld = 0;// 5;
static int numberSpawnGardien = 0;// 4;
static int numberSpawnElite = 0;// 1;
static int numberSpawnRandomAi = 0;// 10;

static float probabilityTourism = 0.85f;
static float probabilityOld = 0.8f;
static float probabilityGardien = 0.5f;
static float probabilityElite = 0.2f;

static TSubclassOf<AMyAICharacter> spawnTourismActor;
static TSubclassOf<AMyAICharacter> spawnOldActor;
static TSubclassOf<AMyAICharacter> spawnGardienActor;
static TSubclassOf<AMyAICharacter> spawnEliteActor;

void  USpawnAI::SetProbabilityTourism(float _probability) {
	probabilityTourism = _probability;
}
void  USpawnAI::SetProbabilityOld(float _probability) {
	probabilityOld = _probability;
}
void  USpawnAI::SetProbabilityGardien(float _probability) {
	probabilityGardien = _probability;
}
void  USpawnAI::SetProbabilityElite(float _probability) {
	probabilityElite = _probability;
}

void  USpawnAI::SetNumberSpawnTourism(int _number) {
	numberSpawnTourism = _number;
}
void  USpawnAI::SetNumberSpawnOld(int _number) {
	numberSpawnOld = _number;
}
void  USpawnAI::SetNumberSpawnGardien(int _number) {
	numberSpawnGardien = _number;
}
void  USpawnAI::SetNumberSpawnElite(int _number) {
	numberSpawnElite = _number;
}
void  USpawnAI::SetNumberSpawnRandom(int _number) {
	numberSpawnRandomAi = _number;
}

void USpawnAI::SetSpawnTourismActor(TSubclassOf<AMyAICharacter> _spawnTourismActor){
	if (_spawnTourismActor == NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,"Null class");
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, _spawnTourismActor->StaticClass()->GetFName().ToString());
	spawnTourismActor = _spawnTourismActor;
}
void  USpawnAI::SetSpawnOldActor(TSubclassOf<AMyAICharacter> _spawnOldActor) {
	if (_spawnOldActor == NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Null class");
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, _spawnOldActor->StaticClass()->GetFName().ToString());
	spawnOldActor = _spawnOldActor;
}
void  USpawnAI::SetSpawnGardienActor(TSubclassOf<AMyAICharacter> _spawnGardienActor) {
	if (_spawnGardienActor == NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Null class");
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, _spawnGardienActor->StaticClass()->GetFName().ToString());
	spawnGardienActor = _spawnGardienActor;
}
void  USpawnAI::SetSpawnEliteActor(TSubclassOf<AMyAICharacter> _spawnEliteActor) {
	if (_spawnEliteActor == NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Null class");
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, _spawnEliteActor->StaticClass()->GetFName().ToString());
	spawnEliteActor = _spawnEliteActor;
}

void  USpawnAI::SetSpawnRayon(float _rayon) {
	spawnRayon = _rayon;
}

void USpawnAI::SpawnAll(UObject* WorldContextObject) {
	SpawnAllRandom(WorldContextObject);
	
	SpawnAllTourism(WorldContextObject);
	SpawnAllOld(WorldContextObject);

	SpawnAllGardien(WorldContextObject);
	SpawnAllElite(WorldContextObject);
}


void USpawnAI::SpawnAllRandom(UObject* WorldContextObject) {
	for (int i = 0; i < numberSpawnRandomAi; i++) {
		SpawnRandom(WorldContextObject);
	}
}

void USpawnAI::SpawnAllTourism(UObject* WorldContextObject) {
	for (int i = 0; i < numberSpawnTourism; i++) {
		SpawnGardien(WorldContextObject);
	}
}

void USpawnAI::SpawnAllOld(UObject* WorldContextObject) {
	for (int i = 0; i < numberSpawnOld; i++) {
		SpawnOld(WorldContextObject);
	}
}

void USpawnAI::SpawnAllGardien(UObject* WorldContextObject) {
	for (int i = 0; i < numberSpawnGardien; i++) {
		SpawnGardien(WorldContextObject);
	}
}

void USpawnAI::SpawnAllElite(UObject* WorldContextObject) {
	for (int i = 0; i < numberSpawnElite; i++) {
		SpawnGardien(WorldContextObject);
	}
}

void USpawnAI::SpawnRandom(UObject* WorldContextObject) {

	int randomValue = UKismetMathLibrary::RandomFloat();
	TArray<float> probability = TArray<float>({ probabilityTourism, probabilityOld, probabilityGardien, probabilityElite });
	
	// Normalize probability
	int len = FCustomThunkTemplates::Array_Length(probability);
	float total = 0.0f;
	for (int i = 0; i < len; i++) {
		total += probability[i];
	}
	for (int i = 0; i < len; i++) {
		probability[i] = probability[i]/total;
	}

	if (randomValue < probability[0]) {
		SpawnTourism(WorldContextObject);
	}
	else if (randomValue < probability[1]) {
		SpawnOld(WorldContextObject);
	}
	else if (randomValue < probability[2]) {
		SpawnGardien(WorldContextObject);
	}
	else {
		SpawnElite(WorldContextObject);
	}
}

void USpawnAI::SpawnTourism(UObject* WorldContextObject) {
	SpawnCharacter(WorldContextObject, spawnTourismActor);
}

void USpawnAI::SpawnOld(UObject* WorldContextObject) {
	SpawnCharacter(WorldContextObject, spawnOldActor);
}

void USpawnAI::SpawnGardien(UObject* WorldContextObject) {
	SpawnCharacter(WorldContextObject, spawnGardienActor);
}

void USpawnAI::SpawnElite(UObject* WorldContextObject) {
	SpawnCharacter(WorldContextObject, spawnEliteActor);
}

void USpawnAI::SpawnCharacter(UObject* WorldContextObject, TSubclassOf<AMyAICharacter> ActorToSpawn) {
	APawn* playPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	FVector spawnLocation(EForceInit::ForceInit);
	bool hasMultipleObjectInSphere = false;
	int32 len{};
	int32 randomInt{};
	TArray<AActor*> sphereOutHit = TArray<AActor*>();

	if (ActorToSpawn) {
		
		playPawn = UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);
		
		if (UKismetSystemLibrary::IsValid(playPawn))
		{
			playerLocation = playPawn->AActor::K2_GetActorLocation();

			TArray<TEnumAsByte<EObjectTypeQuery>> searchPoint = TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 });
			TArray<AActor*> ignorePoint = TArray<AActor*>({ });

			hasMultipleObjectInSphere = UKismetSystemLibrary::SphereOverlapActors(WorldContextObject, playerLocation, spawnRayon,
				searchPoint, false, ignorePoint, /*out*/ sphereOutHit);
		}

		if (!hasMultipleObjectInSphere)
		{
			spawnRayon = spawnRayon + spawnRayon * 0.1f;
			USpawnAI::SpawnCharacter(WorldContextObject, ActorToSpawn);
		}
		else {
			len = FCustomThunkTemplates::Array_Length(sphereOutHit);
			randomInt = UKismetMathLibrary::RandomIntegerInRange(1, len) - 1;
			spawnLocation = sphereOutHit[randomInt]->AActor::K2_GetActorLocation();

			FRotator rot;
			UWorld* world = playPawn->GetWorld();
			if (world) {
				FActorSpawnParameters spawnParams;
				AMyAICharacter* newCharacter = world->SpawnActor<AMyAICharacter>(ActorToSpawn, spawnLocation, rot, spawnParams);
			}
		}
	}

}

void USpawnAI::Respawn(UObject* WorldContextObject, AActor* ActorToRespawn) {
	APawn* playPawn{};
	FVector playerLocation(EForceInit::ForceInit);
	FVector spawnLocation(EForceInit::ForceInit);
	bool hasMultipleObjectInSphere = false;
	int32 len{};
	int32 randomInt{};
	TArray<AActor*> sphereOutHit = TArray<AActor*>();

	playPawn = UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);
	if (UKismetSystemLibrary::IsValid(playPawn))
	{
		playerLocation = playPawn->AActor::K2_GetActorLocation();

		TArray<TEnumAsByte<EObjectTypeQuery>> searchPoint = TArray<TEnumAsByte<EObjectTypeQuery>>({ EObjectTypeQuery::ObjectTypeQuery7 });
		TArray<AActor*> ignorePoint = TArray<AActor*>({ });

		hasMultipleObjectInSphere = UKismetSystemLibrary::SphereOverlapActors(WorldContextObject, playerLocation, spawnRayon,
			searchPoint, false, ignorePoint, /*out*/ sphereOutHit);
	}

	if (!hasMultipleObjectInSphere)
	{
		spawnRayon = spawnRayon + spawnRayon * 0.1f;
		USpawnAI::Respawn(WorldContextObject, ActorToRespawn);
	}
	else {
		len = FCustomThunkTemplates::Array_Length(sphereOutHit);
		randomInt = UKismetMathLibrary::RandomIntegerInRange(1, len) - 1;
		spawnLocation = sphereOutHit[randomInt]->AActor::K2_GetActorLocation();
		spawnLocation.Y = ActorToRespawn->AActor::K2_GetActorLocation().Y;

		ActorToRespawn->AActor::SetActorLocation(spawnLocation);
	}
}