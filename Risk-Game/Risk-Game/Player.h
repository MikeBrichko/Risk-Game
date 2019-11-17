#pragma once
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Dice.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"

class Strategy;

class Player{
private:
	int* playerID;
	std::string* playerName;
	std::vector<Country*>* countriesOwned;
	Hand* hand;
	Deck* gameDeck;
	Map* gameMap;
	Dice* gameDice;
	Strategy* playerStrategy;

	void removeCountryOwned(int countryID);
	int armiesGivenToReinforce();

public:
	Player(int playerID, std::string playerName);
	Player(int playerID, std::string playerName, Deck* pointToDeck);
	Player(int playerID, std::string playerName, Deck* deck, Map* map, Dice* dice);
	Player(int playerID, std::string playerName, Deck* deck, Map* map, Dice* dice, Strategy* newStrategy);
	~Player();

	void conquerEnemyCountry(Country* ownCountry, Country* enemyCountry, std::vector<Player*>* players);
	bool playerAttackDecision();
	bool playerFortificationDecision();

	//PlayerTurn
	void reinforce();
	void attack(std::vector<Player*>* players);
	void fortify();

	//PrintStatements
	void printCountriesOwned();
	void printCardsInHand();
	void printNeighbours(bool areEnemies);
	Country* getCountryOwned(std::string countryOwnedName);
	Country* getNeighbouringCountry(Country* countryOwned, std::string neighbouringCountryName, bool isEnemy);
	
	//Mutators&Accessors
	int getPlayerID();
	std::string getPlayerName();
	int addCardToHand();
	int getAmountOfCountriesOwned();
	int armiesOnCountriesOwned();
	void addCountryOwned(Country* country);
	int getCountriesOwnedSize();
	std::vector<Country*>* getCountriesOwned();
	Map* getGameMap();
	Dice* getGameDice();
	void setPlayerStrategy(Strategy* newStrategy);
};