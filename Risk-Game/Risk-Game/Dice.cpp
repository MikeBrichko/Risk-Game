#include "Dice.h"
#include <vector>
#include <istream>
#include <time.h>

	Dice::Dice(){
		srand(time(NULL)); // Otherwise, it will always return same random values
		tracking = new std::vector<std::vector<int*>*>();
		onceRoll = new std::vector<int*>();
		percentDice = new int[6]();
		numOfRolls = new int(0);
	};

	void Dice::rollDice(int* numOfDice) {
		for (int i = 0; i < *numOfDice; i++) {
			int* random = new int(rand() % 6 + 1);
			percentDice[*random-1]++;
			*numOfRolls += 1;
			onceRoll->push_back(random);
			std::cout << "From dice #" << i+1 << ": " << *random << "\n";
		}
		tracking->push_back(onceRoll);
		onceRoll = new std::vector<int*>();

	}

	void Dice::printCurrentState() {
		//int temp = 0;
		//for (std::vector<int*>::iterator itr = tracking ->begin(); itr != tracking->end(); ++itr) {
		//	++temp;
		//	std::cout << "Dice tracking elemenet " << temp << " :" << **itr << std::endl << "\n";
		//}

		for (int i = 0; i < 6; i++) {
			int* temp1 = &i;
			std::cout << "Dice percentage " << i + 1 << ": " << double(percentDice[i]) / *numOfRolls * 100 << "%\n";
		}
	}
