#include "Dice.h"
#include <vector>
#include <istream>
#include <time.h>
#include <algorithm>

	Dice::Dice(){
		srand(time(NULL));
		diceFaceRolledCounter = new std::vector<int>(6);
		rollCounter = new int(0);
	};

	Dice::~Dice() {
		delete diceFaceRolledCounter;
		delete rollCounter;
	}

	int Dice::diceToBeRolled(int armiesOnCountry, bool attacker) {
		if (attacker) {
			std::cout << "Number of armies on country is: " << armiesOnCountry +1 << std::endl;
		}
		else {
			std::cout << "Number of armies on country is: " << armiesOnCountry - 1 << std::endl;
		}
		if (armiesOnCountry == 1) {
			std::cout << "Since number of armies is 1, the user can only roll one time" <<std::endl;
			return armiesOnCountry;
		}

		int diceToBeRolled = 0;
		while (diceToBeRolled == 0 && 0 < diceToBeRolled < 4) {
			std::cout << "Please enter how many dice will be rolled ";
			if(armiesOnCountry >= 3)
				std::cout << " (input 1, 2 or 3): ";
			else 
				std::cout << " (input 1 or 2): ";
			std::cin >> diceToBeRolled;
		};

		return diceToBeRolled;
	}

	std::vector<int> Dice::rollDice(int armiesOnCountry, bool attacker) {
		int diceToBeRolled = Dice::diceToBeRolled(armiesOnCountry, attacker);
		std::vector<int> diceRolled = std::vector<int>();
		
		int diceFaceRolled = 0;
		for (int i = 0; i < diceToBeRolled; i++) {
			diceFaceRolled = rand() % 6 + 1;
			diceRolled.push_back(diceFaceRolled);
			diceFaceRolledCounter->at((double)diceFaceRolled-1) += 1;
			*rollCounter += 1;
		}

		std::sort(diceRolled.begin(), diceRolled.end());
		return diceRolled;
	}

	void Dice::printDiceFacePercentageRolled() {
		for (int i = 0; i < 6; i++) {
			std::cout << "Percentage of dice face " << i + 1 << " rolled: " << ((double)diceFaceRolledCounter->at(i) / *rollCounter) * 100 << std::endl;
		}
	}
