#include "Dice.h"
#include <vector>
using std::cout;
namespace Dice {
	EachDice::EachDice() {
		tracking;
		int percentDice[] = {0,0,0,0,0,0};
		int numOfRolls = 0;
	};
	void EachDice::storedDiceValue(int addedValue) {
		tracking.push_back(addedValue);
		percentDice[addedValue - 1]++;
		numOfRolls++;
	};
	int EachDice::rollDice() {
		return rand() % 6 + 1;
	}

	void EachDice::printCurrentState() {
		//int temp = 0;
		//for (std::vector<int>::iterator itr = tracking.begin(); itr != tracking.end(); ++itr) {
		//	++temp;
		//	cout << "Dice tracking elemenet " << temp << " :" << *itr << std::endl << "\n";
		//}
		for (int i = 0; i < 6; i++) {
			cout << "Dice percentage " << i + 1 << ": " << double(percentDice[i]) / numOfRolls * 100 << "% ";
		}
	}

	void HowManyDice::setNumOfDice(int numOfDice) {
		val = numOfDice;
	};

	int HowManyDice::getNumOfDice() {
		return val;
	}
	
}