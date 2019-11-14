#pragma once
#include <vector>
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Dice.h"
#include "MapLoader.h"
#include "GameObservers.h"

//This class is the concrete Subject (concrete Observable)
class Player : public ConcreteSubject
{
private:
	int* playerID;
	std::string* playerName;
	std::vector<Country*>* countriesOwned;
	Hand* hand;
	Deck* gameDeck;
	Map* gameMap;
	Dice* gameDice;

	void removeCountryOwned(int countryID);
	void conquerEnemyCountry(Country* ownCountry, Country* enemyCountry, std::vector<Player*>* players);
	bool playerAttackDecision();
	bool playerFortificationDecision();
	void printNeighbours(bool areEnemies);
	Country* getNeighbouringCountry(Country* countryOwned, std::string neighbouringCountryName, bool isEnemy);
	
	// Used for Observer
	Phase* currentPhase;
	std::string* currentPlayerName;
	std::string* currentDefeatedCountry;
	std::vector<std::string*>* currentStats;

public:
	Player(int playerID, std::string playerName);
	Player(int playerID, std::string playerName, Deck* pointToDeck);
	Player(int playerID, std::string playerName, Deck* deck, Map* map, Dice* dice);
	~Player();

	//PlayerTurn
	void reinforce();
	void attack(std::vector<Player*>* players);
	void fortify();

	//PrintStatements
	void printCountriesOwned();
	void printCardsInHand();
	Country* getCountryOwned(std::string countryOwnedName);

	//Mutators&Accessors
	int getPlayerID();
	std::string getPlayerName();
	int addCardToHand();
	int getAmountOfCountriesOwned();
	int armiesOnCountriesOwned();
	void addCountryOwned(Country* country);

	//Need to add implementation of Concrete Subject
	Phase getPhase() override;
	std::string getCurrentPlayerName() override;
	std::vector<std::string*> getStats() override;
	std::string getDefeatedCountryName() override;
};
