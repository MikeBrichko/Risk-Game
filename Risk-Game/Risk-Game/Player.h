#pragma once
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Dice.h"
#include "MapLoader.h"

class Player {
private:
	int* playerID;
	std::string* playerName;
	std::vector<Country*>* countriesOwned;
	Hand* hand;
	Dice* dice;
	static Deck* deck;

	std::vector<Continent*>* continentsOwned;

public:
	Player(int,std::string);
	~Player();
	void addCountryOwned(Country*);
	void addContinentOwned(Continent* continent);

	// Validating reinforce
	int armiesOnCountriesOwned();
	int addArmyToCountry(std :: string, int numOfArmies);

	void reinforce(Map*);
	
	
	//attack(Player* playerAttacked)
	void attack();
	std::vector<std::vector<Country*>> neighbourCountries(bool);
	bool playerAttackDecision(); // Can player attack or not? -> ask to the player.. etc
	bool validateNeighbour(std::string myCountry, std::string otherCountry, bool isAttack);
	bool validateOwnedCountry(std::string countryName);
	void attackOutcome(Country* attker, Country* defender); // Calling dice
	// in attackOutcome, attacker Roll, defender Roll, comparing pair-wise (with sorted dice)
	void moveArmies(Country* from, Country* to); // neighbour country

	 
	void fortify();

	// Return int type
	int addCardToHand();

	void printContinentsOwned();
	void printCountriesOwned();
	void printCarsInHand();
	void rollDice(int);
	int getPlayerID();
	int getAmountOfCountriesOwned();
	void setDeck(Deck* newDeck);
};