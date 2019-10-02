#include <iostream>
#include "Dice.h"
#include <istream>

void getHowManyDice(int& numOfDice);
int main() {

	using std::endl;

	int* numOfDice = new int(0);
	bool* boolRollMore = new bool(true);
	std::string* s1 = new std::string();
	// Player p1 (We don't have a player yet but I will implement as player is implmented)

	//Dice::HowManyDice dNum1 = Dice::HowManyDice();
	//dNum1.setNumOfDice(&numOfDice);

	Dice* d1 = new Dice();
	Dice* d2 = new Dice();
	//Dice* d3 = new Dice();
	while (*boolRollMore) {
		std::cout << "Player 1's turn\n";
		while (*numOfDice == 0 && 0 < *numOfDice < 4) {
			getHowManyDice(*numOfDice);
		};
		d1->rollDice(numOfDice);
		d1->printCurrentState();
		*numOfDice = 0;

		std::cout << "Player 2's turn\n";
		while (*numOfDice == 0 && 0 < *numOfDice < 4) {
			getHowManyDice(*numOfDice);
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

void getHowManyDice(int& numOfDice) {
	std::cout << "Please enter how many dice will be rolled (choose from 1 to 3):";
	std::cin >> numOfDice;

}
