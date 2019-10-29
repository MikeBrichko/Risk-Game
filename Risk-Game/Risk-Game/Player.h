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
	// Validating reinforce
	int armiesOnCountriesOwned();
	void addArmyOnCountry(Country*);
	void reinforce(Map*);
	
	//attack(Player* playerAttacked)
	void attack();
	void attackableCountries();
	bool playerAttackDecision(); // Can player attack or not? -> ask to the player.. etc
	bool validateNeighbour(std::string myCountry, std::string otherCountry, bool isAttack);
	bool validateOwnedCountry(std::string countryName);
	void attackOutcome(Country* attker, Country* defender); // Calling dice
	// in attackOutcome, attacker Roll, defender Roll, comparing pair-wise (with sorted dice)
	void moveArmies(Country* from, Country* to); // neighbour country

	 
	void fortifiy();

	// Return int type
	void addCardToHand(Card*);

	void printCountriesOwned();
	void printCarsInHand();
	void rollDice(int);
	void addCountryOwned(Country* newCountry);
	int getPlayerID();
};