#include "Dice.h"
#include <vector>
#include <istream>

	Dice::Dice(){
	//tracking;
		percentDice = new int[6]();
		numOfRolls = new int(0);
	};
	void Dice::storedDiceValue(int* addedValue) {
		//tracking.push_back(*addedValue);
		percentDice[*addedValue - 1]++;
		*numOfRolls += 1;
	};
	int* Dice::rollDice() {
		int random = rand() % 6 + 1;
		return new int(random);
	}

	void Dice::printCurrentState() {
		//int temp = 0;
		//for (std::vector<int>::iterator itr = tracking.begin(); itr != tracking.end(); ++itr) {
		//	++temp;
		//	cout << "Dice tracking elemenet " << temp << " :" << *itr << std::endl << "\n";
		//}
		for (int i = 0; i < 6; i++) {
			int* temp1 = &i;
			std::cout << "Dice percentage " << i + 1 << ": " << double(percentDice[i]) / *numOfRolls * 100 << "% ";
		}
	}

	//void HowManyDice::setNumOfDice(int* numOfDice) {
	//	val = *numOfDice;
	//};

	//int HowManyDice::getNumOfDice() {
	//	return val;
	//}