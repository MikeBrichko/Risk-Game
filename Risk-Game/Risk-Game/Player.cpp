#include "Player.h"
#include <iostream>
#include <string>

Player::Player(int playerID, std::string playerName) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	continentsOwned = new std::vector<Continent*>();

	hand = new Hand(new std::string(playerName));
	dice = new Dice();

	
}

Player::~Player() {
	delete playerID;
	delete playerName;
	delete countriesOwned;
	delete hand;
	delete dice;
}

void Player::printCountriesOwned() 
{
	std::cout << "These are the countries " << *playerName << " owns: " << std::endl;

	for (auto country : *countriesOwned)
		std::cout << country->getID() << " " << country->getName() << std::endl;
	std::cout << std::endl;
}

void Player::printContinentsOwned()
{
	std::cout << "These are the continents " << *playerName << " owns: " << std::endl;

	for (auto continent : *continentsOwned)
		std::cout << continent->getID() << " " << continent->getName() << std::endl;
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

void Player::addContinentOwned(Continent* continent) {
	continentsOwned->push_back(continent);
}

void Player::addCardToHand(Card* card) {
	hand->addCard(card);
}

void Player::reinforce(Map* gameMap) {
	int armyCount = 0;
	std::cout << "Starting reinforcement phase" << std::endl;

	std::cout << "Adding armies based on COUNTRIES that " << *playerName << " owns."<< std::endl;
	armyCount += floor(countriesOwned->size()/3);
	std::cout << "armies available: " << armyCount << std::endl;
	

	std::cout << "Adding armies based on CONTINENTS that " << *playerName << " owns." << std::endl;
	for (auto continent : *continentsOwned){
			armyCount += continent->getArmyValue();
	}
	std::cout << "armies available: " << armyCount << std::endl;

//	std::cout << "Adding armies based on Cards that " << *playerName << " owns." << std::endl;
//	//armyCount += addCard();
//	//change existin mthod to return a number
//
//	std::cout << "Place Armies." << std::endl;
//	printCountriesOwned();
//	//loop based on armyCount where there is a addArmy()
//	//addArmy() will cmake sure that the player has effectively placed this exact number of 
//	//new armies somewhere on the map by the end of the reinforcement phase.
//
//	std::cout << "Finished reinforcement phase" << std::endl;
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