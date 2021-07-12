// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyAICharacter.h"
#include "SpawnAI.generated.h"

/**
 * 
 */
UCLASS()
class ZOOSMASH_API USpawnAI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	private:
		static void SpawnCharacter(UObject* WorldContextObject, TSubclassOf<AMyAICharacter> ActorToSpawn);

	public:

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetSpawnTourismActor(TSubclassOf<AMyAICharacter> _spawnTourismActor);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetSpawnOldActor(TSubclassOf<AMyAICharacter> _spawnOldActor);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetSpawnGardienActor(TSubclassOf<AMyAICharacter> _spawnGardienActor);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetSpawnEliteActor(TSubclassOf<AMyAICharacter> _spawnEliteActor);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetSpawnRayon(float _rayon);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetProbabilityTourism(float _probability);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetProbabilityOld(float _probability);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetProbabilityGardien(float _probability);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SetProbabilityElite(float _probability);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void  SetNumberSpawnTourism(int _number);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void  SetNumberSpawnOld(int _number);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void  SetNumberSpawnGardien(int _number);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void  SetNumberSpawnElite(int _number);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void  SetNumberSpawnRandom(int _number);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnAll(UObject* WorldContextObject);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnAllRandom(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnAllTourism(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnAllOld(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnAllGardien(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnAllElite(UObject* WorldContextObject);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnRandom(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnTourism(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnOld(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnGardien(UObject* WorldContextObject);
		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void SpawnElite(UObject* WorldContextObject);

		UFUNCTION(BlueprintCallable, Category = "Custom IA")
			static void Respawn(UObject* WorldContextObject, AActor* respawnPawn);

};
