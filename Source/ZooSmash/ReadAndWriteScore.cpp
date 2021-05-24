// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadAndWriteScore.h"
#include <fstream>
#include <string>
#include <vector>

struct Score
{
	std::string name;
	int date, time, cost;

	Score(std::string _name, int _date, int _time, int _cost) {
		name = _name;
		date = _date;
		time = _time;
		cost = _cost;
	}
};

std::vector<Score> listScore;

UReadAndWriteScore::UReadAndWriteScore()
{
	listScore = {};
} 

void UReadAndWriteScore::WriteNewScore()
{
	std::ifstream infile("score.txt");
}

void UReadAndWriteScore::ReadNewScore()
{
	std::ifstream infile("score.txt");
	
	std::string name;

	int date, time, cost;
	if (infile) {
		while (infile >> date >> time >> cost >> name)
		{
			Score s = Score(name, date, time, cost);
			listScore.push_back(s);
		}
	}
}

void UReadAndWriteScore::AddScoreUI()
{

}

void UReadAndWriteScore::BeginPlay(){
	ReadNewScore();
}

void UReadAndWriteScore::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

}
