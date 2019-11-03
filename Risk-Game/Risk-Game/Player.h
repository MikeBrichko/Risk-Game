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
	Deck* gameDeck;
	Map* gameMap;

public:
	Player(int playerID, std::string playerName);
	Player(int playerID, std::string playerName, Deck* pointToDeck);
	Player(int playerID, std::string playerName, Deck* deck, Map* map);
	~Player();
	void addCountryOwned(Country*);

	// Validating reinforce
	int armiesOnCountriesOwned();
	int addArmyToCountry(std :: string, int numOfArmies);
	bool validateCountryInput(std::string cInput);

	void reinforce();
	
	
	//attack(Player* playerAttacked)
	void attack();
	std::vector<std::vector<Country*>> neighbourCountries(bool);
	bool playerAttackDecision();
	void fortify();
	int addCardToHand();
	void printCountriesOwned();
	void printCarsInHand();
	void rollDice(int);
	int getPlayerID();
	int getAmountOfCountriesOwned();
};