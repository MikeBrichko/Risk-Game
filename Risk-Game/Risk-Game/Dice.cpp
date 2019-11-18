#include "Dice.h"
#include <vector>
#include <istream>
#include <time.h>
#include <algorithm>

	Dice::Dice(){
		diceFaceRolledCounter = new std::vector<int>(6);
		rollCounter = new int(0);
	};

	Dice::~Dice() {
		delete diceFaceRolledCounter;
		delete rollCounter;
	}

	int Dice::diceToBeRolledByAttacker(int armiesOnCountry, bool isComputer) {

		if (armiesOnCountry == 1) {
			std::cout << "Since number of armies is 1, the user can only roll one time" <<std::endl;
			return armiesOnCountry;
		}

		if (isComputer) {
			if (armiesOnCountry == 2)
				return armiesOnCountry;
			else
				return 3;
		}

		int diceToBeRolled = 0;
		while (true) {
			std::cout << "Please enter how many dice will be rolled ";
			if (armiesOnCountry >= 3) {
				std::cout << " (input 1, 2 or 3): ";
				std::cin >> diceToBeRolled;

				if (diceToBeRolled == 1 || diceToBeRolled == 2 || diceToBeRolled == 3)
					return diceToBeRolled;
				else
					std::cout << "Invalid amount of dice selected" << std::endl;
			}
			else {
				std::cout << " (input 1 or 2): ";
				std::cin >> diceToBeRolled;
				if (diceToBeRolled == 1 || diceToBeRolled == 2)
					return diceToBeRolled;
				else
					std::cout << "Invalid amount of dice selected" << std::endl;
			}
		};

		return diceToBeRolled;
	}

	int Dice::diceToBeRolledByDefender(int armiesOnCountry, bool isComputer) {

		if (armiesOnCountry == 1) {
			std::cout << "Since number of armies is 1, the user can only roll one time" << std::endl;
			return armiesOnCountry;
		}

		if (isComputer) {
			return 2;
		}

		int diceToBeRolled = 0;
		while (true) {
			std::cout << "Please enter how many dice will be rolled ";
			std::cout << " (input 1 or 2): ";
			std::cin >> diceToBeRolled;

			if (diceToBeRolled == 1 || diceToBeRolled == 2)
				return diceToBeRolled;
			else
				std::cout << "Invalid amount of dice selected" << std::endl;
		}

		return diceToBeRolled;
	}

	std::vector<int> Dice::rollDice(int armiesOnCountry, bool isAttacking, bool isComputer) {
		int diceToBeRolled = 0;
		if(isAttacking)
			diceToBeRolled = Dice::diceToBeRolledByAttacker(armiesOnCountry, isComputer);
		else
			diceToBeRolled = Dice::diceToBeRolledByDefender(armiesOnCountry, isComputer);
		std::vector<int> diceRolled = std::vector<int>();
		
		int diceFaceRolled = 0;
		srand((unsigned int)time(NULL));
		for (int i = 0; i < diceToBeRolled; i++) {
			diceFaceRolled = rand() % 6 + 1;
			diceRolled.push_back(diceFaceRolled);
			diceFaceRolledCounter->at(static_cast<unsigned __int64>(diceFaceRolled-1.0)) += 1;
			*rollCounter += 1;
		}

		std::sort(diceRolled.begin(), diceRolled.end(), std::greater<int>());
		return diceRolled;
	}

	void Dice::printDiceFacePercentageRolled() {
		for (int i = 0; i < 6; i++) {
			std::cout << "Percentage of dice face " << i + 1 << " rolled: " << ((double)diceFaceRolledCounter->at(i) / *rollCounter) * 100 << std::endl;
		}
	}