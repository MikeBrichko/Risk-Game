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
class Player : public Subject  
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


};

class DisplayInfo : public Observer //Similar to DigitalClock.h in notes
{
	//this is class as the Concrete Observer
public:
	DisplayInfo();
	//DisplayInfo(parameter);
	~DisplayInfo();
	void Update();
	void display();
private:
	//something
}