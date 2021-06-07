// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveSystem.generated.h"

USTRUCT(BlueprintType)
struct FHighscore {
	GENERATED_USTRUCT_BODY()

	// FHighscores(FString name, int32 score, int32 time) : name(name), score(score), time(time) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = TEXT("");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 time = 0;
};

/**
 * Allows saving and loading highscore data to/from binary files
 */
UCLASS()
class ZOOSMASH_API USaveSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	static bool Save();
	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	static bool Load();
	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	static TArray<FHighscore> GetHighscores();
	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	static void SetHighscores(TArray<FHighscore> scores);
};
