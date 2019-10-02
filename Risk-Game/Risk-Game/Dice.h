#pragma once


#include <iostream>
#include <vector>
#include <istream>

class Dice
{
public:
	Dice();
	void rollDice(int* numOfDices);
	void printCurrentState();
private:
	int* percentDice;
	int* numOfRolls;
	std::vector<int*>* currentRollingDice;
	std::vector<std::vector<int*>*>* recordsOfRolling;
};
