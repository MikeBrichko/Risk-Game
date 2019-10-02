#include <iostream>
#include "Dice.h"
#include <istream>

int main() {

	using std::endl;

	int* numOfDice = new int(0);
	bool* boolRollMore = new bool(true);
	std::string* s1 = new std::string();

	Dice* d1 = new Dice();
	Dice* d2 = new Dice();
	while (*boolRollMore) {
		std::cout << "Player 1's turn\n";
		while (*numOfDice == 0 && 0 < *numOfDice < 4) {
			std::cout << "Please enter how many dice will be rolled (choose from 1 to 3):";
			std::cin >> *numOfDice;
		};
		d1->rollDice(numOfDice);
		d1->printCurrentState();
		*numOfDice = 0;

		std::cout << "Player 2's turn\n";
		while (*numOfDice == 0 && 0 < *numOfDice < 4) {
			std::cout << "Please enter how many dice will be rolled (choose from 1 to 3):";
			std::cin >> *numOfDice;
		};
		d2->rollDice(numOfDice);
		d2->printCurrentState();
		*numOfDice = 0;

		std::cout << "Would you like to roll more dice? (Y/N)";
		std::cin >> *s1;
		if (*s1 == "Y" || *s1 =="y") {
			*boolRollMore = true;
		}
		else {
			*boolRollMore = false;
		}
	
	}

}
