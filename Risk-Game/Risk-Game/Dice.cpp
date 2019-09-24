#include "Dice.h"
#include <vector>
using std::cout;
namespace Dice {
	EachDice::EachDice() {
		tracking;
	};
	void EachDice::storedDiceValue(int addedValue) {
		tracking.push_back(addedValue);
	};
	int EachDice::rollDice() {
		return rand() % 6 + 1;
	}

	void EachDice::printCurrentState() {
		int temp = 0;
		for (std::vector<int>::iterator itr = tracking.begin(); itr != tracking.end(); ++itr) {
			++temp;
			cout << "Dice tracking elemenet " << temp << " :" << *itr << std::endl << "\n";
		}
	}

	void HowManyDice::setNumOfDice(int numOfDice) {
		val = numOfDice;
	};

	int HowManyDice::getNumOfDice() {
		return val;
	}
	
}