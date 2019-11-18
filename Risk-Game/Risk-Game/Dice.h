#pragma once


#include <iostream>
#include <vector>
#include <istream>

class Dice
{
public:
	Dice();
	~Dice();
	std::vector<int> rollDice(int armiesOnCountry, bool isAttacking, bool isComputer);
	void printDiceFacePercentageRolled();
private:
	std::vector<int>* diceFaceRolledCounter;
	int* rollCounter;
	int diceToBeRolledByAttacker(int armiesOnCountry, bool isComputer);
	int diceToBeRolledByDefender(int armiesOnCountry, bool isComputer);
};
