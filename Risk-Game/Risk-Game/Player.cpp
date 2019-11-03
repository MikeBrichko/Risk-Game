#include "Player.h"
#include <iostream>
#include <string>

Player::Player(int playerID, std::string playerName) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	dice = new Dice();
}

Player::Player(int playerID, std::string playerName, Deck* deck) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	dice = new Dice();
	gameDeck = deck;
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
		std::cout << country->getID() << " " << country->getName() << std::endl;
	std::cout << std::endl;
}

void Player::printCarsInHand() {
	std::cout << "These are the cards " << *playerName << " owns: ";
	hand->printCardsInHand();
}

void Player::rollDice(int armiesOnCountry) {
	std::vector<int> diceRolled = dice->rollDice(armiesOnCountry);
	std::cout << *playerName << " rolled: ";
	for (auto diceFace : diceRolled)
		std::cout << diceFace << " ";
	std::cout << std::endl;
}

void Player::addCountryOwned(Country* country) {
	countriesOwned->push_back(country);
}

int Player::addCardToHand() {
	return hand->addCard(gameDeck->draw());
}

int Player::addArmyToCountry(std::string countryName, int numOfArmies){
	int numArmies=0;

	for (auto country : *countriesOwned) {
		if (country->getName() == countryName) {
			std::cout << country->getName() << " had " << country->getArmies() << std::endl;
			numArmies = country->getArmies();
			numArmies += numOfArmies;
			country->setArmies(numArmies);

			std::cout << country->getName() << " now has " << country->getArmies() << std::endl;	
			return numOfArmies;
		}
	}

	return numArmies;
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
		std::cout << "\n" << continent->getName() << std::endl;

		for (auto countries : *continentCountries) {
			std::cout << countries->getName() << std::endl;
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
			std::cout << "invalid number. Please enter a value between 0 and " << armiesToAdd << " inclusively" << std::endl;
			std::cin >> armyInput;
		}
		addArmyToCountry(countryInput, armyInput);
		armiesLeftToAdd -= armyInput;
		i += (armyInput-1);
	}
	
	std::cout << "Number of armies added: " << armiesAdded <<std::endl;
	if (armiesOnCountriesOwned() == armiesToAdd)
	{
		std::cout << "all armies successfully added.\n\n" << std::endl;
	}

	std::cout << "=====================Finished reinforcement phase=========================" << std::endl;
}


void Player::attack() {

	std::cout << "Starting Attack Phase" << std::endl;
	//std::cout << *playerName << " picks what country he attacks" << std::endl;
	std::cout << "List of countries " << *playerName << " can attack: " << std::endl;
	//this->attackableCountries();

	//print countries that can be attacked by which country
	//dont print country with less than 2 armies on it
	//Example
	//Country A can attack Country B,C,D
	//Country E can attack F,G
	//etc...
	bool decision = playerAttackDecision();
	while (decision == true)
	{
		std::cout << *playerName <<" chooses to attack" << std::endl;

		std::cout << "List of countries " << *playerName << " can attack: " << std::endl;
		std::vector<std::vector<Country*>> listOfNeighbours = this->neighbourCountries(true);
		bool validateAttacking = true;
		while (validateAttacking){
			std::cout << "Please choose a player's country from attack from the list above (enter country number)" << std::endl;

			int countryFrom;
			std::cin >> countryFrom;
			std::cout << "Please choose a enemy's country to attack from the list above (enter country number)" << std::endl;
			int countryToAttack;
			std::cin >> countryToAttack;
			std::cout << listOfNeighbours[0][0]->getID() << std::endl;
			for (auto country : listOfNeighbours) {
				if (country[0]->getID() == countryFrom) {
					for (auto neighbour : country) {
						if (neighbour->getID() == countryToAttack && neighbour->getID() != countryFrom) {
							validateAttacking = false;
						}
					}
				}
			}
		}
		//while loop -> playerAttack() returns boolean
		//select country to attack
		//void attackOutcome(Country* X, Country* Y);
		//within the method above -> void removeArmy(Country*)
	}
	std::cout << "Finished Attack Phase" << std::endl;
}

std::vector<std::vector<Country*>> Player::neighbourCountries(bool isAttack) {
	//std::cout << "Please choose an attackable countries from :" << std::endl;

	std::cout << "Countries you own     -------->      Neighbouring enemy countries to attack" << std::endl;
	std::cout << "-----------------                    --------------------------------------" << std::endl;
	std::vector<std::vector<Country*>> listOfNeighbours = std::vector<std::vector<Country*>>();
	for (auto country : *countriesOwned) 
	{
		std::vector<Country *> neighbours = std::vector<Country *>();
		neighbours.push_back(country);
		for (auto neighbour : country->getNeighbours()) {
			if (isAttack) {
				if (neighbour->getID() != *this->playerID) {
					neighbours.push_back(neighbour);
				}
			}
			else {
				if (neighbour->getID() == *this->playerID) {
					neighbours.push_back(neighbour);
				}
			}
		}
		if (neighbours.size() > 1) {
			if (isAttack) {
				std::cout << country->getName() << "(" << country->getID() << ") Has neighbours ";
				for (int i = 1; i < neighbours.size(); i++) {
					std::cout << neighbours[i]->getName() << "(" << neighbours[i]->getID() << ") ";
				}
				std::cout << std::endl;
			}
			else {
				std::cout << country->getName() << "(" << country->getID() << ") Has armies: " << country->getArmies() << " with neighbours" <<std::endl;
				for (int i = 1; i < neighbours.size(); i++) {
					std::cout << "\t" << neighbours[i]->getName() << "(" << neighbours[i]->getID() << "): armies of " << neighbours[i]->getArmies() << std::endl;
				}
			}

		}
		listOfNeighbours.push_back(neighbours);
	}
	return listOfNeighbours;
}

bool Player::playerAttackDecision()
{
	//todo: Need to check if player can attack

	bool attack;
	std::string decision;

	std::cout << "\nWould you like to attack a country? (yes/no)" << std::endl;
	std::cin >> decision;
	if ((decision == "yes") || (decision == "y"))
	{
		attack = true;
		//std::cout << "you chose to attack" << std::endl;
	}
	else if ((decision == "no") || (decision == "n"))
	{
		attack = false;
		std::cout << "You chose not to attack" << std::endl;
	}
	else
	{
		attack = false;
		std::cout << "You chose not to attack" << std::endl;
	}
	return attack;

}

void Player::fortify() {
	std::cout << "Starting fortification phase" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	bool validateFortify = true;
	std::vector<std::vector<Country*>> listOfNeighbours = this->neighbourCountries(false);

	while (validateFortify) {
		std::cout << "Please choose a player's country from attack from the list above (enter country number)" << std::endl;

		int countryFrom;
		std::cin >> countryFrom;
		std::cout << "Please choose a enemy's country to attack from the list above (enter country number)" << std::endl;
		int countryToAttack;
		std::cin >> countryToAttack;
		std::cout << listOfNeighbours[0][0]->getID() << std::endl;
		for (auto country : listOfNeighbours) {
			if (country[0]->getID() == countryFrom) {
				for (auto neighbour : country) {
					if (neighbour->getID() == countryToAttack && neighbour->getID() != countryFrom) {
						validateFortify = false;
					}
				}
			}
		}
	}

	std::cout << "Please choose how many you want to remove from " << std::endl;
	std::cout << "Please choose a enemy's country to attack from the list above (enter country number)" << std::endl;

	//if(player want to move armies){
	//Countries that can move armies: 
	//Country A to Country B, C or E
	//Country C to Country A, Country E or Country H
	//moveArmies(Country* X, Country* Y)
	//}
	std::cout << "Finished fortification phase" << std::endl;
}

int Player::getPlayerID() {
	return *playerID;
}

int Player::getAmountOfCountriesOwned() {
	return countriesOwned->size();
}