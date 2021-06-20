// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem.h"
#include "SortHighScore.h"
#include <math.h>  

bool  USortHighScore::KeyIsSmaller(TArray<FHighscore>& Array_score, int32 i, int32 j, int keyIndex) {
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("KeyIsSmaller")));

	bool isSmaller = false;
	if (keyIndex == 0) {
		isSmaller = Array_score[i].name > Array_score[j].name;
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Array_score[i].name);
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Array_score[j].name);
	}
	else if (keyIndex == 1) {
		isSmaller = Array_score[i].score > Array_score[j].score;
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%u"), Array_score[i].score));
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%u"), Array_score[j].score));
	}
	else if (keyIndex == 2) {
		isSmaller = Array_score[i].time > Array_score[j].time;
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%u"), Array_score[i].time));
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%u"), Array_score[j].time));
	}
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), isSmaller));
	return isSmaller;
}

TArray<FHighscore> USortHighScore::Sort(UPARAM(ref) TArray<FHighscore> &Array_score, bool Descending, int keyIndex)
{
	int32 m = Array_score.Num();			// Return the array size 
	int32 j, i;

	// Sort
	for (j = 1; j < m; j++)
	{
		i = j - 1; 
		FHighscore key = Array_score[j];
		while (i >= 0 && KeyIsSmaller(Array_score, i, j, keyIndex))
		{
			Array_score[i + 1] = Array_score[i];
			i--;
		}
		Array_score[i + 1] = key;
	}

	// Reverse the Array
	if (Descending) {
		for (j = 0; j < floor( (m - 1)/2 ); j++) {
			auto key = Array_score[j];
			Array_score[j] = Array_score[m - 1 - j];
			Array_score[m - 1 - j] = key;
		}
	}

	return Array_score;
}