// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

static TArray<FHighscore> highscores;
static const std::string filename = "savefile.data";
static const int version = 1;

void USaveSystem::SetHighscores(TArray<FHighscore> values)
{
	highscores = values;
}

TArray<FHighscore> USaveSystem::GetHighscores()
{
	return highscores;
}

bool USaveSystem::Save()
{
	const FString ffile = FPaths::Combine(FPaths::ProjectDir(), FString(filename.c_str()));
	const std::string file = std::string(TCHAR_TO_UTF8(*ffile));

	std::ofstream writer(file,std::ios::binary);
	if (!writer)
		return false;

	writer.write((char *)&version, sizeof(int));
	const int numEntries = highscores.Num();
	writer.write((char*)&numEntries, sizeof(int));
	for(FHighscore highscore : highscores) {
		const int nameLen = highscore.name.Len();
		writer.write((char*)&nameLen, sizeof(int));
		for (int j = 0; j < highscore.name.Len(); j++)
			writer.write((char*)&highscore.name[j], sizeof(TCHAR));
		writer.write((char*)&highscore.score, sizeof(int));
		writer.write((char*)&highscore.time, sizeof(int));
	}

	writer.close();

	return true;
}

bool USaveSystem::Load()
{
	const FString ffile = FPaths::Combine(FPaths::ProjectDir(), FString(filename.c_str()));
	const std::string file = std::string(TCHAR_TO_UTF8(*ffile));

	std::ifstream reader(file, std::ios::binary);
	if (!reader)
		return false;

	int v;
	reader.read((char*)&v, sizeof(v));
	if (v != version)
		return false;

	TArray<FHighscore> tmp_highscores;

	int n;
	reader.read((char*)&n, sizeof(n));

	for (int i = 0; i < n; i++) {
		int l;
		reader.read((char*)&l, sizeof(l));
		TCHAR* name = (TCHAR*)malloc(l * sizeof(TCHAR));
		for (int j = 0; j < l; j++) {
			reader.read((char*)&name[j], sizeof(TCHAR));
		}
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), name));
		int score;
		reader.read((char*)&score, sizeof(score));

		int time;
		reader.read((char*)&time, sizeof(time));

		FHighscore highscore;
		highscore.name = name;
		highscore.score = score;
		highscore.time = time;

		tmp_highscores.Add(highscore);
	}

	reader.close();

	highscores = tmp_highscores;

	return true;
}
