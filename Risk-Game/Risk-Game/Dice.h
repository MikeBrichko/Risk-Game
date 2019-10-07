#pragma once


#include <iostream>
#include <vector>
#include <istream>

class Dice
{
public:
	Dice();
	~Dice();
	std::vector<int> rollDice(int armiesOnCountry);
	void printDiceFacePercentageRolled();
private:
	std::vector<int>* diceFaceRolledCounter;
	int* rollCounter;
	int diceToBeRolled(int armiesOnCountry);
};
