#include "PlayerStrategies.h"
#include <iostream>
#include <string>
#include <algorithm>

Player::Player(int playerID, std::string playerName) {
	playerStrategy = new HumanPlayer();
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = NULL;
	gameMap = NULL;
	gameDice = NULL;
	currentPhase = new Phase();
	currentPlayerName = new std::string();
	currentDefeatedCountry = new std::string();
	currentStats = new std::vector<std::string*>();
}

Player::Player(int playerID, std::string playerName, Deck* deck) {
	playerStrategy = new HumanPlayer();
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = deck;
	gameMap = NULL;
	gameDice = NULL;
	currentPhase = new Phase();
	currentPlayerName = new std::string();
	currentDefeatedCountry = new std::string();
	currentStats = new std::vector<std::string*>();
}

Player::Player(int playerID, std::string playerName, Deck* deck, Map* map, Dice* dice) {
	playerStrategy = new HumanPlayer();
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = deck;
	gameMap = map;
	gameDice = dice;
	currentPhase = new Phase();
	currentPlayerName = new std::string();
	currentDefeatedCountry = new std::string();
	currentStats = new std::vector<std::string*>();
}

Player::Player(int playerID, std::string playerName, Deck* deck, Map* map, Dice* dice, Strategy* newStrategy) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	playerStrategy = newStrategy;
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = deck;
	gameMap = map;
	gameDice = dice;
	currentPhase = new Phase();
	currentPlayerName = new std::string();
	currentDefeatedCountry = new std::string();
	currentStats = new std::vector<std::string*>();
}

Player::~Player() {
	delete playerID;
	delete playerName;
	delete countriesOwned;
	delete hand;
	gameDeck = NULL;
	gameMap = NULL;
	gameDice = NULL;
	delete currentPhase;
	delete currentPlayerName;
	delete currentDefeatedCountry;
	for (auto stats : *currentStats)
		delete stats;
	delete currentStats;
}

int Player::armiesGivenToReinforce() {
	int armiesToAdd = 0;
	//Adding armies based on COUNTRIES that the player owns
	armiesToAdd += static_cast<int>(floor(getCountriesOwned()->size() / 3));

	//Adding armies based on CONTINENTS that the player owns
	std::vector<Country* > tempCountriesVector = std::vector<Country*>();
	int comparedID;
	for (auto continent : *gameMap->getContinents()) {
		for (auto country : *continent->getCountries()) {
			comparedID = country->getID();
			for (auto countryOwned : *getCountriesOwned()) {
				if (comparedID == countryOwned->getID()) {
					tempCountriesVector.push_back(countryOwned);
				}
			}
		}
		if (tempCountriesVector.size() == gameMap->getContinents()->size()) {
			armiesToAdd += continent->getArmyValue();
		}
		tempCountriesVector.clear();
	}

	//Adding armies based on the cards that player owns
	armiesToAdd += this->addCardToHand();
	return armiesToAdd;
}

int Player::armiesOnCountriesOwned() {
	int armieCount = 0;
	for (auto country : *countriesOwned)
		armieCount += country->getArmies();
	return armieCount;
}

void Player::printCountriesOwned()
{
	std::cout << "These are the countries " << *playerName << " owns: " << std::endl;
	for (auto country : *countriesOwned)
	{
		std::cout << country->getID() << ". " << country->getName() << " (" << country->getArmies() << " armies)" << std::endl;
	}
}

void Player::printCardsInHand() {
	std::cout << "These are the cards " << *playerName << " owns: ";
	hand->printCardsInHand();
}

void Player::addCountryOwned(Country* country) {
	countriesOwned->push_back(country);
	country->setPlayerID(*playerID);
}

void Player::removeCountryOwned(int countryID) {
	for (int i = 0; i < countriesOwned->size(); i++) {
		if (countriesOwned->at(i)->getID() == countryID) {
			countriesOwned->erase(countriesOwned->begin() + i);
		}
	}
}

void Player::conquerEnemyCountry(Country* ownCountry, Country* enemyCountry, std::vector<Player*>* players) {
	std::cout << "You have defeated " << enemyCountry->getName() << std::endl;

	//Step 1. Remove Country from Enemy Player
	for (auto player : *players) {
		if (enemyCountry->getPlayerID() == player->getPlayerID())
			player->removeCountryOwned(enemyCountry->getID());
		*currentPlayerName = player->getPlayerName();
	}

	//Step 2. Add Country to countriesOwned
	addCountryOwned(enemyCountry);
	*currentPhase = LOSE_COUNTRY;

	for (auto player : *players) {
		double percentNumber = (double(player->getAmountOfCountriesOwned()) / double(gameMap->getNumOfCountries()) * 100);
		std::string percent = std::to_string(percentNumber);
		std::string truncatedPercent = percent.substr(0, 5);
		currentStats->push_back(new std::string(player->getPlayerName() + " controls " + truncatedPercent + "% of world map\n"));

	}

	*currentDefeatedCountry = enemyCountry->getName();
	notify();
	for (auto text : *currentStats) {
		delete text;
		text = NULL;
	}
	delete currentStats;
	currentStats = new std::vector<std::string*>();
	std::vector<Player*>::iterator i = players->begin();
	while (i != players->end()) {
		if ((*i)->getAmountOfCountriesOwned() == 0) {
			*currentPhase = DEFEATED;
			notify();

			players->erase(i--);
			delete (*i);
			break;
		}
		else {
			++i;
		}
	}

	//Step 3. Mobilize armies to newly aquired country
	int armiesToMobilize = 0;
	while (true) {
		std::cout << ownCountry->getName() << " has " << ownCountry->getArmies() << " armies." << std::endl;
		std::cout << "How many armies would you like to move from the attacking country to the defeated country?" << std::endl;
		std::cin >> armiesToMobilize;

		if (armiesToMobilize <= (ownCountry->getArmies() - 1) && armiesToMobilize >= 1)
			break;
		else
			std::cout << "Can't move that many armies! Select the amount of armies in between 1 and " << ownCountry->getArmies() - 1 << std::endl;
	}

	ownCountry->addArmy(-armiesToMobilize);
	enemyCountry->addArmy(armiesToMobilize);
}

bool Player::playerAttackDecision()
{
	bool ableToAttack = false;
	for (auto country : *countriesOwned) {
		if (country->getArmies() >= 2) {
			ableToAttack = true;
			break;
		}
	}

	if (ableToAttack == false) {
		std::cout << "You do not have sufficient resources to perform an attack." << std::endl;
		return false;
	}

	bool attack = false;
	std::string decision = "";
	while (ableToAttack) {
		std::cout << "Would you like to attack a country? (yes/no)" << std::endl;
		std::cin >> decision;
		if ((decision == "yes") || (decision == "y")) {
			attack = true;
			break;
		}
		else if ((decision == "no") || (decision == "n")) {
			attack = false;
			std::cout << "You chose not to attack" << std::endl;
			break;
		}
		else {
			std::cout << "Please enter valid option" << std::endl;
		}
	}

	return attack;
}

bool Player::playerFortificationDecision() {
	std::string decision;
	while (true) {
		std::cout << "Would you like to fortify one of your countries? (yes/no)" << std::endl;
		std::cin >> decision;

		if (decision == "yes" || decision == "y")
			return true;
		else if (decision == "no" || decision == "n")
			return false;
		else
			std::cout << "Invalid input!" << std::endl;
	}
}

int Player::getPlayerID() {
	return *playerID;
}

std::string Player::getPlayerName() {
	return *playerName;
}

int Player::addCardToHand() {
	return hand->addCard(gameDeck->draw());
}

int Player::getAmountOfCountriesOwned() {
	return static_cast<int>(countriesOwned->size());
}

int Player::getCountriesOwnedSize() {
	return static_cast<int> (countriesOwned->size());
}

std::vector<Country*>* Player::getCountriesOwned() {
	return countriesOwned;
}

Map* Player::getGameMap() {
	return gameMap;
}

Dice* Player::getGameDice() {
	return gameDice;
}

void Player::printNeighbours(bool areEnemies) {
	for (auto country : *countriesOwned) {
		if (areEnemies)
			std::cout << country->getID() << "." << country->getName() << " (" << country->getArmies() << " armies) has enemy neighbours: " << std::endl;
		else
			std::cout << country->getID() << "." << country->getName() << " (" << country->getArmies() << " armies) has friendly neighbours: " << std::endl;
		for (auto neighbouringCountry : country->getNeighbours()) {
			if (areEnemies) {
				if (neighbouringCountry->getPlayerID() != *playerID) {
					std::cout << "\t" << neighbouringCountry->getID() << "." << neighbouringCountry->getName() << " (" << neighbouringCountry->getArmies() << " armies)" << std::endl;
				}

			}
			else {
				std::cout << "\t" << neighbouringCountry->getID() << "." << neighbouringCountry->getName() << " (" << neighbouringCountry->getArmies() << " armies)" << std::endl;
			}
		}
	}
}

Country* Player::getNeighbouringCountry(Country* countryOwned, std::string neighbouringCountryName, bool isEnemy) {
	for (auto neighbouringCountry : countryOwned->getNeighbours()) {
		if (isEnemy) {
			if (neighbouringCountry->getName() == neighbouringCountryName && neighbouringCountry->getPlayerID() != *playerID)
				return neighbouringCountry;
		}
		else {
			if (neighbouringCountry->getName() == neighbouringCountryName && neighbouringCountry->getPlayerID() == *playerID)
				return neighbouringCountry;
		}
	}
	return NULL;
}

Country* Player::getCountryOwned(std::string countryOwnedName) {
	for (auto country : *countriesOwned) {
		if (country->getName() == countryOwnedName)
			return country;
	}
	return NULL;
}

void Player::setPlayerStrategy(Strategy* newStrategy) {
	playerStrategy = newStrategy;
}

void Player::reinforce() {
	std::cout << "=====================Starting reinforcement phase=====================" << std::endl;
	*currentPhase = REINFORCE;
	notify();
	printCountriesOwned();
	playerStrategy->reinforce(this, armiesGivenToReinforce());
	printCountriesOwned();
	std::cout << "=====================Ending reinforcement phase=====================" << std::endl;
}

void Player::attack(std::vector<Player*>* players) {
	std::cout << "=====================Starting attack phase=====================" << std::endl;
	*currentPhase = ATTACK;
	notify();
	playerStrategy->attack(this, players);
	std::cout << "=====================Ending attack phase=====================" << std::endl;
}

void Player::fortify() {
	std::cout << "=====================Starting fortification phase=====================" << std::endl;
	*currentPhase = FORTIFY;
	notify();
	printNeighbours(false);
	playerStrategy->fortify(this);
	printNeighbours(false);
	std::cout << "=====================Ending fortification phase=====================" << std::endl;
}

Phase Player::getPhase() {
	return *currentPhase;
}

std::string Player::getCurrentPlayerName() {
	if (*currentPhase == DEFEATED || *currentPhase == LOSE_COUNTRY) {
		return *currentPlayerName;
	}
	else {
		return *playerName;
	}
}

std::string Player::getDefeatedCountryName() {
	return *currentDefeatedCountry;
}

std::vector<std::string*> Player::getStats() {
	return *currentStats;
}

void Player::setCurrentPhase(Phase newPhase) {
	*currentPhase = newPhase;
}