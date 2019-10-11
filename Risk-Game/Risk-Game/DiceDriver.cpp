#include <iostream>
#include "Dice.h"
#include <istream>


int main() {
	int armiesOnCountry = 0;
	std::string s1 = "";

	std::cout << "Creating a Dice object" << std::endl;
	Dice* dice = new Dice();

	int numOfRolls = 0;
	std::cout << "Enter the amount of time you want to roll the dice: ";
	std::cin >> numOfRolls;

	std::vector<int> diceRolled = std::vector<int>();
	while (numOfRolls != 0) {
		armiesOnCountry = rand() % 3 + 1;
		diceRolled = dice->rollDice(armiesOnCountry);
		for (auto diceFace : diceRolled) {
			std::cout << "Rolled value: " <<diceFace << std::endl;
		}
		numOfRolls--;
	}
	dice->printDiceFacePercentageRolled();
}

