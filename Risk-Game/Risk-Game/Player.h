#pragma once
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Dice.h"

class Player {
private:
	static std::vector<Player>* playerList;
	int* playerID;
	std::string* playerName;
	std::vector<Country*>* countriesOwned;
	Hand* hand;
	Dice* dice;

public:
	Player(int,std::string);
	~Player();
	void addCountryOwned(Country*);
	void removeCountryOwned(int countryID);
	int getPlayerID();
	std::vector<Country*> getCountriesOwned();
	// Validating reinforce
	int armiesOnCountriesOwned();
	void addArmyOnCountry(Country*);

	void reinforce(Map*);
	
	//attack(Player* playerAttacked)
	void attackableCountries();
	void attack(std::vector<Player*>*);
	std::vector<std::vector<Country*>> neighbourCountries(bool);
	bool playerAttackDecision(); // Can player attack or not? -> ask to the player.. etc
	bool validateNeighbour(std::string myCountry, std::string otherCountry, bool isAttack);
	bool validateOwnedCountry(std::string countryName);
	void attackOutcome(Country* attker, Country* defender); // Calling dice
	// in attackOutcome, attacker Roll, defender Roll, comparing pair-wise (with sorted dice)
	void moveArmies(Country* from, Country* to); // neighbour country

	 
	void fortify();

	// Return int type
	void addCardToHand(Card*);

	//void printNeighbourCountries(Country*);
	void printCountriesOwned();
	void countriesCanAttackWith();
	void printCarsInHand();
	std::vector<int> rollDice(int,bool);
};