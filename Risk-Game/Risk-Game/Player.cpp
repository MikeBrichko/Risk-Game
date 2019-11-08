#include "Player.h"
#include <iostream>
#include <string>
#include <algorithm>

Player::Player(int playerID, std::string playerName) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	dice = new Dice();
	gameDeck = NULL;
	gameMap = NULL;
}

Player::Player(int playerID, std::string playerName, Deck* deck) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	dice = new Dice();
	gameDeck = deck;
	gameMap = NULL;
}

Player::Player(int playerID, std::string playerName, Deck* deck, Map* map) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	dice = new Dice();
	gameDeck = deck;
	gameMap = map;
}

Player::~Player() {
	delete playerID;
	delete playerName;
	delete countriesOwned;
	delete hand;
	delete dice;
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
		std::cout << country->getID() << " " << country->getName() << std::endl;
	}
	std::cout << std::endl;
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

void Player::addArmyToCountry(std::string countryName, int numOfArmies){
	for (auto country : *countriesOwned) {
		if (country->getName() == countryName) {
			std::cout << country->getName() << " had " << country->getArmies() << std::endl;
			country->addArmy(numOfArmies);
			std::cout << country->getName() << " now has " << country->getArmies() << std::endl;	
		}
	}
}

std::vector<std::vector<Country*>> Player::neighbouringEnemyCountries(bool isAnEnemyNeighbour) {
	//std::cout << "Please choose an attackable countries from :" << std::endl;
	std::vector<std::vector<Country*>> listOfNeighbours = std::vector<std::vector<Country*>>();
	for (auto country : *countriesOwned)
	{
		if (country->getArmies() >= 2) {
			std::vector<Country*> neighbours = std::vector<Country*>();
			neighbours.push_back(country);
			for (auto neighbour : country->getNeighbours()) {
				if (isAnEnemyNeighbour) {
					if (neighbour->getPlayerID() != *this->playerID) {
						neighbours.push_back(neighbour);
					}
				}
				else {
					if (neighbour->getPlayerID() == *this->playerID) {
						neighbours.push_back(neighbour);
					}
				}
			}

			if (neighbours.size() > 1) {
				if (isAnEnemyNeighbour) {
					std::cout << country->getID() << "." << country->getName() << " (" << country->getArmies() << " armies) has enemy neighbours: " << std::endl;
					for (int i = 1; i < neighbours.size(); i++) {
						std::cout << "\t" << neighbours[i]->getID() << "." << neighbours[i]->getName() << " (" << neighbours[i]->getArmies() << " armies)" << std::endl;
					}
				}
				else {
					std::cout << country->getID() << "." << country->getName() << " (" << country->getArmies() << " armies)" << " with ally neighbours: " << std::endl;
					for (int i = 1; i < neighbours.size(); i++) {
						std::cout << "\t" << neighbours[i]->getID() << "." << neighbours[i]->getName() << " (" << neighbours[i]->getArmies() << " armies)" << std::endl;
					}
				}
				listOfNeighbours.push_back(neighbours);
			}
		}
	}
	return listOfNeighbours;
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
		std::cout << "You do not have sufficient resources to perform an attack" << std::endl;
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

bool Player::validateCountryInput(std::string cInput) {
	for (auto countries : *countriesOwned) {
		if (cInput == countries->getName()) {
			return true;
		}
	}
	return false;
}

void Player::reinforce() {
	int armiesToAdd = 0;
	int armiesAdded = 0;

	std::cout << "=====================Starting reinforcement phase=====================" << std::endl;

	std::cout << "Adding armies based on COUNTRIES that " << *playerName << " owns." << std::endl;
	armiesToAdd += floor(countriesOwned->size() / 3);

	std::cout << "Adding armies based on CONTINENTS that " << *playerName << " owns." << std::endl;
	std::vector<Continent*>* continents = gameMap->getContinents();
	std::vector<Country* >* tempCountriesVector = new std::vector<Country*>();

	int comparedID;
	for (auto continent : *continents) {
		std::vector<Country*>* continentCountries = continent->getCountries();

		for (auto countries : *continentCountries) {
			comparedID = countries->getID();

			for (auto countries : *countriesOwned) {
				if (comparedID == countries->getID()) {
					tempCountriesVector->push_back(countries);
				}
			}
		}

		if (tempCountriesVector->size() == continentCountries->size()) {
			armiesToAdd += continent->getArmyValue();
		}
		tempCountriesVector->clear();
	}
	delete tempCountriesVector;
	tempCountriesVector = NULL;

	std::cout << "Adding armies based on CARDS that " << *playerName << " owns." << std::endl;
	armiesToAdd += addCardToHand();

	printCountriesOwned();

	std::string countryInput;
	int armyInput;
	int armiesLeftToAdd = armiesToAdd;
	for (int i = 0; i < armiesToAdd; i++) {
		std::cout << "armies available to place: " << armiesLeftToAdd << "\n" << std::endl;
		std::cout << "\nfor which country would you like to add armies? (enter country name)" << std::endl;
		std::cin >> countryInput;
		while (!validateCountryInput(countryInput)) {
			std::cout << "invalid string. input a Country Name" << std::endl;
			std::cin >> countryInput;
		}
		std::cout << "how many armies to add to this country?" << std::endl;
		std::cin >> armyInput;
		while (armyInput < 0 || (armiesLeftToAdd - armyInput) < 0) {
			std::cout << "invalid number. Please enter a value between 0 and " << armiesLeftToAdd << " inclusively" << std::endl;
			std::cin >> armyInput;
		}
		addArmyToCountry(countryInput, armyInput);
		armiesLeftToAdd -= armyInput;
		i += (armyInput - 1);
	}

	std::cout << "Number of armies added: " << armiesAdded << std::endl;
	if (armiesOnCountriesOwned() == armiesToAdd)
	{
		std::cout << "all armies successfully added.\n\n" << std::endl;
	}

	std::cout << "=====================Finished reinforcement phase=========================" << std::endl;
}

void Player::attack(std::vector<Player*>* players) {
	std::cout << "=====================Starting Attack Phase=====================" << std::endl;
	std::cout << "For " << *playerName << std::endl;

	std::vector<std::vector<Country*>> listOfNeighbours = this->neighbouringEnemyCountries(true);
	Player* enemyPlayer{};
	int countryFromID;
	Country* attackingCountry = NULL;
	Country* defendingCountry = NULL;
	int attackingCountryIndex = 0;
	std::vector<int> attackingDice;
	std::vector<int> defendingDice;

	while (playerAttackDecision())
	{
		//Step 1: Select the attacking country
		while (true)
		{
			std::cout << "Please enter the number of the country that you would like to attack with: " << std::endl;
			std::cin >> countryFromID;
			for (auto country : listOfNeighbours) {
				if (country[0]->getID() == countryFromID) {
					attackingCountry = country[0];
					break;
				}
				attackingCountryIndex++;
			}

			if (attackingCountry != NULL) {
				if (attackingCountry->getArmies() >= 2)
					break;
			}
			else
				std::cout << "Invalid choice. You need to choose a country with at least 2 armies" << std::endl;
		}

		//Step 2. Select the defending country
		int countryToAttackID;
		while (true) {
			std::cout << "Please enter the number of the country that you want to attack: " << std::endl;
			std::cin >> countryToAttackID;
			for (auto country : listOfNeighbours.at(attackingCountryIndex)) {
				if (country->getID() == countryToAttackID) {
					defendingCountry = country;
					break;
				}
			}

			if (defendingCountry == NULL)
				std::cout << "Please make sure you entered correct country number." << std::endl;
			else
				break;
		}

		//Step 3. Roll Dices
		//Attacker Dice Roll
		std::cout << "Attacker rolls" << std::endl;
		attackingDice = dice->rollDice(attackingCountry->getArmies(), true);
		std::cout << "Attacking Player rolled: ";
		for (auto diceFace : attackingDice)
			std::cout << diceFace << " ";
		std::cout << std::endl;

		//Defender Dice Roll
		std::cout << "Defender rolls " << std::endl;
		defendingDice = dice->rollDice(defendingCountry->getArmies(), false);
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
		listOfNeighbours = this->neighbouringEnemyCountries(true);
	}
	std::cout << "=====================Finished Attack Phase=====================" << std::endl;
}

void Player::fortify() {
	std::cout << "=====================Starting fortification phase=====================" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	bool validateFortify = true;
	std::vector<std::vector<Country*>> listOfNeighbours = this->neighbouringEnemyCountries(false);
	Country* removingCountry = NULL;
	int removingCountryIndex = 0;
	Country* addingCountry = NULL;

	//Step 1. Select Country having armies removed
	int countryFrom;
	while (true)
	{
		std::cout << "Please enter the number of the country that you would like to remove armies from: " << std::endl;
		std::cin >> countryFrom;
		for (auto country : listOfNeighbours) {
			if (country[0]->getID() == countryFrom) {
				removingCountry = country[0];
				break;
			}
			removingCountryIndex++;
		}

		if (removingCountry != NULL) {
			if (removingCountry->getArmies() >= 2)
				break;
		}
		else
			std::cout << "Invalid choice." << std::endl;
	}

	//Step 2. Select Friendly Neighbour
	int countryTo = 0;
	while (true) {
		std::cout << "Please enter the number of the country that you want to transfer armies to: " << std::endl;
		std::cin >> countryTo;
		for (auto country : listOfNeighbours.at(removingCountryIndex)) {
			if (country->getID() == countryTo) {
				addingCountry = country;
				break;
			}
		}

		if (addingCountry == NULL)
			std::cout << "Please make sure you entered correct country numbers." << std::endl;
		else
			break;
	}

	//Step 3. Move armies to friendly Country
	int armiesToMobilize = 0;
	while (true) {
		std::cout << removingCountry->getName() << " has " << removingCountry->getArmies() << " armies." << std::endl;
		std::cout << "How many armies would you like to move from " << removingCountry->getName() <<" to " << addingCountry->getName() << "?" << std::endl;
		std::cin >> armiesToMobilize;

		if (armiesToMobilize <= (removingCountry->getArmies() - 1) && armiesToMobilize >= 1)
			break;
		else
			std::cout << "Can't move that many armies! Select the amount of armies in between 1 and " << removingCountry->getArmies() - 1 << std::endl;
	}

	removingCountry->addArmy(-armiesToMobilize);
	addingCountry->addArmy(armiesToMobilize);

	listOfNeighbours = this->neighbouringEnemyCountries(false);
	std::cout << "=====================Finished fortification phase=====================" << std::endl;
}

//Accessors and Mutators
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