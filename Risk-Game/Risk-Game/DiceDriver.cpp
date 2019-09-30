#include <iostream>
#include "Dice.h"
#include <string>
using namespace std;

void getHowManyDice(int& numOfDice);
int main() {

	using std::endl;

	int numOfDice = 0;
	bool boolRollMore = true;
	string s1 = "";
	while (numOfDice == 0 && 0 < numOfDice < 4) {
		getHowManyDice(numOfDice);
	};

	// Player p1 (We don't have a player yet but I will implement as player is implmented)

	Dice::HowManyDice dNum1 = Dice::HowManyDice();
	dNum1.setNumOfDice(numOfDice);

	Dice::EachDice d1 = Dice::EachDice();
	Dice::EachDice d2 = Dice::EachDice();
	Dice::EachDice d3 = Dice::EachDice();
	while (boolRollMore) {
		switch (numOfDice)
		{
		case 3:
			d3.storedDiceValue(d3.rollDice());
			cout << "Dice 3 Information\n";
			d3.printCurrentState();
			cout << "Dice 3 ends\n";
		case 2:
			d2.storedDiceValue(d2.rollDice());
			cout << "Dice 2 Information\n";
			d2.printCurrentState();
			cout << "Dice 2 ends\n";
		case 1:
			d1.storedDiceValue(d1.rollDice());
			cout << "Dice 1 Information\n";
			d1.printCurrentState();
			cout << "Dice 1 ends\n";
			break;
		}
		cout << "Would you like to roll more dice? (Y/N)";
		cin >> s1;
		if (s1 == "Y") {
			boolRollMore = true;
		}
		else {
			boolRollMore = false;
		}
	
	}

}

void getHowManyDice(int& numOfDice) {
	cout << "Please enter how many dice will be rolled (choose from 1 to 3):";
	cin >> numOfDice;

}
