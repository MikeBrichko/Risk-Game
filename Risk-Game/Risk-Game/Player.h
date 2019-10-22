#pragma once
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Dice.h"

class Player {
private:
	int* playerID;
	std::string* playerName;
	std::vector<Country*>* countriesOwned;
	Hand* hand;
	Dice* dice;

public:
	Player(int,std::string);
	~Player();
	void reinforce();
	//attack(Player* playerAttacked)
	void attack();
	void fortifiy();
	void addCountryOwned(Country*);
	void addCardToHand(Card*);
	void printCountriesOwned();
	void printCarsInHand();
	void rollDice(int);
};