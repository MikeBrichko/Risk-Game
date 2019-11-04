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
	static std::vector<Player*>* listOfPlayer;
	int* playerID;
	std::string* playerName;
	std::vector<Country*>* countriesOwned;
	Hand* hand;
	Dice* dice;
	Deck* gameDeck;
	Map* gameMap;

	void removeCountryOwned(int countryID);
	void conquerEnemyCountry(Country* ownCountry, Country* enemyCountry, std::vector<Player*>* players);
	std::vector<std::vector<Country*>> neighbouringEnemyCountries(bool);
	bool validateCountryInput(std::string cInput);
	bool playerAttackDecision();

public:
	Player(int playerID, std::string playerName);
	Player(int playerID, std::string playerName, Deck* pointToDeck);
	Player(int playerID, std::string playerName, Deck* deck, Map* map);
	~Player();

	//PlayerTurn
	void reinforce();
	void attack(std::vector<Player*>* players);
	void fortify();

	//PrintStatements
	void printCountriesOwned();
	void printCardsInHand();
	
	//Mutators&Accessors
	int getPlayerID();
	std::string getPlayerName();
	int addCardToHand();
	int getAmountOfCountriesOwned();
	int armiesOnCountriesOwned();
	void addArmyToCountry(std::string countryName, int numOfArmies);
	void addCountryOwned(Country* country);
};