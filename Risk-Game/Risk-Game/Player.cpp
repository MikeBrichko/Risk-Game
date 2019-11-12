#include "Player.h"
#include <iostream>
#include <string>
#include <algorithm>

Player::Player(int playerID, std::string playerName) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = NULL;
	gameMap = NULL;
	gameDice = NULL;
}

Player::Player(int playerID, std::string playerName, Deck* deck) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = deck;
	gameMap = NULL;
	gameDice = NULL;
}

Player::Player(int playerID, std::string playerName, Deck* deck, Map* map, Dice* dice) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	gameDeck = deck;
	gameMap = map;
	gameDice = dice;
}

Player::~Player() {
	delete playerID;
	delete playerName;
	delete countriesOwned;
	delete hand;
	gameDeck = NULL;
	gameMap = NULL;
	gameDice = NULL;
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

void Player::printCardsInHand(){
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
	}

	//Step 2. Add Country to countriesOwned
	addCountryOwned(enemyCountry);

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
	for (auto country : *countriesOwned){
		if (country->getArmies() >= 2){
			ableToAttack = true;
			break;
		}
	}

	if (ableToAttack == false){
		std::cout << "You do not have sufficient resources to perform an attack." << std::endl;
		return false;
	}

	bool attack = false;
	std::string decision = "";
	while (ableToAttack) {
		std::cout << "Would you like to attack a country? (yes/no)" << std::endl;
		std::cin >> decision;
		if ((decision == "yes") || (decision == "y")){
			attack = true;
			break;
		}
		else if ((decision == "no") || (decision == "n")){
			attack = false;
			std::cout << "You chose not to attack" << std::endl;
			break;
		}else{
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
	return countriesOwned->size();
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

void Player::reinforce() {
	notify(Phase::REINFORCE);
	int armiesToAdd = 0;
	std::cout << "Adding armies based on COUNTRIES that " << *playerName << " owns." << std::endl;
	armiesToAdd += floor(countriesOwned->size() / 3);

	std::cout << "Adding armies based on CONTINENTS that " << *playerName << " owns." << std::endl;
	std::vector<Country* > tempCountriesVector = std::vector<Country*>();
	int comparedID;
	for (auto continent : *gameMap->getContinents()) {
		for (auto country : *continent->getCountries()) {
			comparedID = country->getID();
			for (auto countryOwned : *countriesOwned) {
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

	std::cout << "Adding armies based on CARDS that " << *playerName << " owns." << std::endl;
	armiesToAdd += addCardToHand();

	printCountriesOwned();

	std::string countryOwnedName;
	int armyInput;
	int armiesLeftToAdd = armiesToAdd;
	Country* countryToAddArmiesTo = NULL;
	for (int i = 0; i < armiesToAdd; i++) {
		std::cout << "Armies available to place: " << armiesLeftToAdd << "." << std::endl << std::endl;

		//Step 1. Select Owned Country
		while (true) {
			std::cout << "Please enter the name of the country that you would like to add armies to:" << std::endl;
			std::cin >> countryOwnedName;
			countryToAddArmiesTo = getCountryOwned(countryOwnedName);

			if (countryToAddArmiesTo != NULL)
				break;
			else
				std::cout << "Invalid input! You do not own " << countryOwnedName << "." << std::endl;
		}

		//Step 2. Add armies to selected country
		while (true) {
			std::cout << "How many armies would you like to add to " << countryOwnedName << "?" << std::endl;
			std::cin >> armyInput;

			if (armyInput < 0 || (armiesLeftToAdd - armyInput) < 0)
				std::cout << "Invalid input! Please enter a value between 0 and " << armiesLeftToAdd << " inclusively." << std::endl;
			else
				break;
		}

		countryToAddArmiesTo->addArmy(armyInput);
		armiesLeftToAdd -= armyInput;
		i += (armyInput - 1);
	}

	std::cout << "=====================Finished reinforcement phase=========================" << std::endl;
}

void Player::attack(std::vector<Player*>* players) {
	notify(Phase::ATTACK);
	std::cout << "For " << *playerName << std::endl;
	printNeighbours(true);

	std::string attackingCountryName;
	Country* attackingCountry = NULL;
	std::vector<int> attackingDice;

	std::string defendingCountryName;
	Country* defendingCountry = NULL;
	std::vector<int> defendingDice;

	while (playerAttackDecision())
	{
		//Step 1: Select the attacking country
		while (true)
		{
			std::cout << "Please enter the name of the country that you would like to attack with: " << std::endl;
			std::cin >> attackingCountryName;
			attackingCountry = getCountryOwned(attackingCountryName);

			if (attackingCountry != NULL) {
				if (attackingCountry->getArmies() >= 2)
					break;
				else
					std::cout << "Invalid input! " << attackingCountryName << " has less than 2 armies." << std::endl;
			}
			else
				std::cout << "Invalid input! You do not own " << attackingCountryName << "." << std::endl;
		}

		//Step 2. Select the defending country
		while (true) {
			std::cout << "Please enter the name of the country that you want to attack: " << std::endl;
			std::cin >> defendingCountryName;
			defendingCountry = getNeighbouringCountry(attackingCountry, defendingCountryName, true);

			if (defendingCountry != NULL)
				break;
			else
				std::cout << "Invalid input! " << defendingCountryName << " is not an enemy country."<< std::endl;
		}

		//Step 3. Roll Dices
		//Attacker Dice Roll
		std::cout << "Attacker rolls" << std::endl;
		attackingDice = gameDice->rollDice(attackingCountry->getArmies(), true);
		std::cout << "Attacking Player rolled: ";
		for (auto diceFace : attackingDice)
			std::cout << diceFace << " ";
		std::cout << std::endl;

		//Defender Dice Roll
		std::cout << "Defender rolls " << std::endl;
		defendingDice = gameDice->rollDice(defendingCountry->getArmies(), false);
		std::cout << "Defending Player rolled: ";
		for (auto diceFace : defendingDice)
			std::cout << diceFace << " ";
		std::cout << std::endl;

		//Dice Roll Outcome
		int minimumSize = (attackingDice.size() < defendingDice.size() ? attackingDice.size() : defendingDice.size());
		for (int i = 0; i < minimumSize; i++) {
			if (attackingDice[i] <= defendingDice[i]) {
				attackingCountry->addArmy(-1);

				if (attackingCountry->getArmies() == 1)
					break;
			}
			else {
				defendingCountry->addArmy(-1);
				if (defendingCountry->getArmies() == 0) {
					conquerEnemyCountry(attackingCountry, defendingCountry, players);
				}
			}
		}

		printNeighbours(true);
	}
	std::cout << "=====================Finished Attack Phase=====================" << std::endl;
}

void Player::fortify() {
	notify(Phase::FORTIFY);
	std::cout << "Moving armies to different countries" << std::endl;
	printNeighbours(false);

	//Step 1. Select Country having armies removed
	Country* transferingCountry = NULL;
	std::string transferingCountryName;
	while (playerFortificationDecision()) {
		while (true)
		{
			std::cout << "Please enter the name of the country that you would like to transfer armies from: " << std::endl;
			std::cin >> transferingCountryName;
			transferingCountry = getCountryOwned(transferingCountryName);

			if (transferingCountry != NULL) {
				if (transferingCountry->getArmies() >= 2)
					break;
				else
					std::cout << "Invalid input! " << transferingCountryName << " has less than 2 armies." << std::endl;
			}
			else
				std::cout << "Invalid choice! You do not own " << transferingCountryName << "." << std::endl;
		}

		//Step 2. Select Friendly Neighbour
		Country* receivingCountry = NULL;
		std::string receivingCountryName;
		while (true) {
			std::cout << "Please enter the name of the country that you would like to receive armies: " << std::endl;
			std::cin >> receivingCountryName;
			receivingCountry = getNeighbouringCountry(transferingCountry, receivingCountryName, false);

			if (receivingCountry != NULL)
				break;
			else
				std::cout << "Invalid choice! " << receivingCountryName << " is not a friendly neighbour of " << transferingCountryName << "." << std::endl;
		}

		//Step 3. Move armies to friendly Country
		int armiesToMobilize = 0;
		while (true) {
			std::cout << transferingCountryName << " has " << transferingCountry->getArmies() << " armies." << std::endl;
			std::cout << "How many armies would you like to move from " << transferingCountryName << " to " << receivingCountryName << "?" << std::endl;
			std::cin >> armiesToMobilize;

			if (armiesToMobilize <= (transferingCountry->getArmies() - 1) && armiesToMobilize >= 0)
				break;
			else
				std::cout << "Can't move that many armies! Select the amount of armies in between 1 and " << transferingCountry->getArmies() - 1 << std::endl;
		}

		transferingCountry->addArmy(-armiesToMobilize);
		receivingCountry->addArmy(armiesToMobilize);
		break;
	}
	std::cout << "=====================Finished fortification phase=====================" << std::endl;
}