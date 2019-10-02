#pragma once


#include <iostream>
#include <vector>
#include <istream>

class Dice
{
public:
	std::vector<std::vector<int*>*>* tracking;
	Dice();
	void rollDice(int* numOfDices);
	void printCurrentState();
private:
	int* percentDice;
	int* numOfRolls;
	std::vector<int*>* onceRoll;
};
