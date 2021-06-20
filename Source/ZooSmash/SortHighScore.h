// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveSystem.h"
#include "SortHighScore.generated.h"

/**
 * 
 */
UCLASS()
class ZOOSMASH_API USortHighScore : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Sorting Functions")
		static bool KeyIsSmaller(TArray<FHighscore>& Array_score, int32 i, int32 j, int keyIndex);
	UFUNCTION(BlueprintCallable, Category = "Sorting Functions")
		static TArray<FHighscore> Sort(UPARAM(ref) TArray<FHighscore> &Array_score, bool Descending, int index);
	
};
