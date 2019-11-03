#include "Player.h"
#include "Dice.h"
#include <iostream>
#include <string>

std::vector<Player*>* Player::listOfPlayer = new std::vector<Player*>();
Player::Player(int playerID, std::string playerName) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
	hand = new Hand(new std::string(playerName));
	dice = new Dice();
	listOfPlayer;
}

Player::~Player() {
	delete playerID;
	delete playerName;
	delete countriesOwned;
	delete hand;
	delete dice;
}

void Player::addListOfPlayer(Player* player) {
	listOfPlayer->push_back(player);
}

int Player::armiesOnCountriesOwned() {
	int armieCount = 0;
	for (auto country : *countriesOwned)
		armieCount += country->getArmies();
	return armieCount;
}

int Player::getAmountOfCountriesOwned() {
	return countriesOwned->size();
}
int Player::getPlayerID() {
	return *playerID;
}
std::vector<Country*> Player::getCountriesOwned() {
	return *countriesOwned;
};

void Player::printCountriesOwned()
{
	std::cout << "These are the countries " << *playerName << " owns: " << std::endl;
	for (auto country : *countriesOwned)
	{
		std::cout << country->getID() << " " << country->getName() << std::endl;
	}
	std::cout << std::endl;

}

void Player::printCarsInHand() {
	std::cout << "These are the cards " << *playerName << " owns: ";
	hand->printCardsInHand();
}

void Player::addCountryOwned(Country* country) {
	countriesOwned->push_back(country);
}

void Player::removeCountryOwned(int countryID) {
	int remove = NULL;
	std::cout << countriesOwned->size();
	for (int i = 0; i < countriesOwned->size(); i++) {
		if ((*countriesOwned)[i]->getID() == countryID) {
			remove = i;
		}
	}
	if (remove) {
		countriesOwned->erase(countriesOwned->begin() + remove);
	}
	std::cout << countriesOwned->size();

}

std::string Player::getPlayerName() {
	return *playerName;
}

void Player::addCardToHand(Card* card) {
	hand->addCard(card);
}

void Player::reinforce(Map* gameMap) {
//	int armieCount = 0;
//	std::cout << "Starting reinforcement phase" << std::endl;
//
//	std::cout << "Adding armies based on Countries that " << *playerName << " owns."<< std::endl;
//	armieCount += floor(countriesOwned->size()/3);
//
//	std::cout << "Adding armies based on Continents that " << *playerName << " owns." << std::endl;
//	//armieCount += continentsOwned();
//
//	std::cout << "Adding armies based on Cards that " << *playerName << " owns." << std::endl;
//	//armieCount += addCard();
//	//change existin mthod to return a number
//
//	std::cout << "Place Armies." << std::endl;
//	printCountriesOwned();
//	//loop based on armieCount where there is a addArmy()
//	//addArmy() will cmake sure that the player has effectively placed this exact number of 
//	//new armies somewhere on the map by the end of the reinforcement phase.
//
//	std::cout << "Finished reinforcement phase" << std::endl;
}


void Player::attack() {

	std::cout << "Starting Attack Phase" << std::endl;
	std::cout << "For " << *playerName <<"\n"<< std::endl;

	std::vector<std::vector<Country*>> listOfNeighbours = this->neighbourCountries(true);
	Player* enemyPlayer{};

	bool decision = playerAttackDecision();
	while (decision == true)
	{
		if (listOfNeighbours.size() < 1) {
			std::cout << *playerName << " cannot attack any countries (All his own countries have only 1 army)" << std::endl;
			break;
		}
		int countryFromID;
		int countryToAttackID;
		Country* countryFrom = NULL;
		Country* countryToAttack = NULL;

		bool validateAttacking = true;
		while (validateAttacking) {

			//Need to check if the country has less than 2 armies
			bool correctCountry = false;
			while (correctCountry == false)
			{
				std::cout << "Please choose one of your countries to start the attack. It must have at least 2 armies." << std::endl;
				std::cout << "(enter country number)" << std::endl;
				std::cin >> countryFromID;
				for (auto country : listOfNeighbours) {
					if (country[0]->getID() == countryFromID) {
						countryFrom = country[0];
					}
				}

				if (countryFrom->getArmies() < 2)
				{
					std::cout << "Invalid choice. You need to choose a country with at least 2 armies" << std::endl;
				}
				else
					correctCountry = true;
			}

			std::cout << "Please choose an enemy's country to attack (enter country number)." << std::endl;
			std::cin >> countryToAttackID;
			for (auto country : listOfNeighbours) {
				if (country[0]->getID() == countryFromID) {
					countryFrom = country[0];
					for (auto neighbour : country) {
						if (neighbour->getID() == countryToAttackID && neighbour->getID() != countryFromID) {
							countryToAttack = neighbour;
							validateAttacking = false;
						}
					}
				}
			}
			if (validateAttacking) {
				std::cout << "Please make sure you entered correct country numbers." << std::endl;
			}
		}

		std::vector<int> attackDice;
		std::vector<int> enemyDice;
		attackDice = dice->rollDice(countryFrom->getArmies() - 1);
		std::cout << *playerName << " rolled: ";
		for (auto diceFace : attackDice)
			std::cout << diceFace << " ";
		std::cout << std::endl;
		for (auto player : *listOfPlayer) {
			if (player->getPlayerID() == countryToAttack->getPlayerID()) {
				enemyPlayer = player;
				if (countryToAttack->getArmies() > 2) {
					enemyDice = enemyPlayer->dice->rollDice(2);
				}
				else {
					enemyDice = enemyPlayer->dice->rollDice(countryToAttack->getArmies());

				}
				std::cout << enemyPlayer->getPlayerName() << " rolled: ";
				for (auto diceFace : enemyDice)
					std::cout << diceFace << " ";
				std::cout << std::endl;
			}
		}

		std::vector<int>::iterator ptr;
		int minimumSize = (attackDice.size() < enemyDice.size() ? attackDice.size() : enemyDice.size());
		for (int i = 0; i < minimumSize; i++) {
			if (attackDice[attackDice.size()-1-i] <= enemyDice[enemyDice.size() - 1 -i]) {
				countryFrom->addArmy(countryFrom->getArmies() - 1);
			}
			else {
				countryToAttack->addArmy(countryToAttack->getArmies()-1);
			}
		}
		std::cout << "------------------------------------------------" << std::endl;
		std::cout << countryFrom->getName() <<" now has " << countryFrom->getArmies() << " armies." << std::endl;
		std::cout << countryToAttack->getName() << " now has " << countryToAttack->getArmies() << " armies." << std::endl;

		if (countryToAttack->getArmies() == 0) 
		{
			

			int numArmiesToMove;
			bool correctNumOfArmies = false;

			std::cout << "You have defeated the defending country" << std::endl;
			while (correctNumOfArmies == false)
			{
				std::cout << "How many armies would you like to move from the attacking country to the defeated country?" << std::endl;

				std::cin >> numArmiesToMove;

				if (numArmiesToMove > (countryFrom->getArmies() - 1)) 
					std::cout << "Can't move that many armies! (leave at least 1 army on attacking)" << std::endl;
				else
					correctNumOfArmies = true;
			}

			//Decrement num of armies from attacking Country
			countryFrom->addArmy(countryFrom->getArmies() - numArmiesToMove);

			//Increment num of armies from defeated Country
			countryToAttack->addArmy(countryToAttack->getArmies() + numArmiesToMove);

			std::cout << "Your armies successfully moved!" << std::endl;

			std::cout << countryFrom->getName() <<" now has " << countryFrom->getArmies() <<" armies" << std::endl;
			std::cout << countryToAttack->getName() << " now has " << countryToAttack->getArmies() << " armies" << std::endl;

			//Add defeated country to players "countriesOwned" list
			addCountryOwned(countryToAttack);
			countryToAttack->setPlayerID(this->getPlayerID());

			//Remove defeated country from opponent players "countriesOwned" list
			enemyPlayer->removeCountryOwned(countryToAttack->getID());

		}
		listOfNeighbours = this->neighbourCountries(true);

		decision = playerAttackDecision();
	}
	std::cout << "Finished Attack Phase" << std::endl;
}

std::vector<std::vector<Country*>> Player::neighbourCountries(bool isAttack) {
	//std::cout << "Please choose an attackable countries from :" << std::endl;
	std::cout << std::endl;
	std::vector<std::vector<Country*>> listOfNeighbours = std::vector<std::vector<Country*>>();
	for (auto country : *countriesOwned) 
	{
		if (country->getArmies() >= 2) {
			std::vector<Country*> neighbours = std::vector<Country*>();
			neighbours.push_back(country);
			for (auto neighbour : country->getNeighbours()) {
				if (isAttack) {
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
				if (isAttack) {
					std::cout << country->getID() << "." << country->getName() << " (" << country->getArmies() << " armies)   has enemy neighbours:   ";
					for (int i = 1; i < neighbours.size(); i++) {
						std::cout << neighbours[i]->getID() << "." << neighbours[i]->getName() << " (" << neighbours[i]->getArmies() << " armies)   ";
					}
					std::cout << std::endl;
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
	

	//check if player is able to attack
	bool ableToAttack = false;
	for (auto country : *countriesOwned)
	{
		if (country->getArmies() >= 2)
		{
			ableToAttack = true;
		}
	}
	if(ableToAttack == false)
	{
		std::cout << "You do not have sufficient resources to perform an attack" << std::endl;
	}
	std::cout << std::endl;

	bool attack;
	std::string decision;


	while (true) {
		std::cout << "\nWould you like to attack a country? (yes/no)" << std::endl;
		std::cin >> decision;
		if ((decision == "yes") || (decision == "y"))
		{
			attack = true;
			break;
		}
		else if ((decision == "no") || (decision == "n"))
		{
			attack = false;
			std::cout << "You chose not to attack" << std::endl;
			break;
		}
		else
		{
			std::cout << "Please enter valid option" << std::endl;
		}
	}

	return attack;

}

void Player::fortify() {
	std::cout << "Starting fortification phase" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	bool validateFortify = true;
	std::vector<std::vector<Country*>> listOfNeighbours = this->neighbourCountries(false);
	Country* removingCountry = NULL;
	Country* addingCountry = NULL;
	while (validateFortify) {
		std::cout << "Please choose a country to move armies from (enter country number)" << std::endl;

		int countryFrom;
		std::cin >> countryFrom;
		std::cout << "Please choose a country to move armies to (enter country number)" << std::endl;
		int countryToAttack;
		std::cin >> countryToAttack;
		for (auto country : listOfNeighbours) {
			if (country[0]->getID() == countryFrom) {
				removingCountry = country[0];
				for (auto neighbour : country) {
					if (neighbour->getID() == countryToAttack && neighbour->getID() != countryFrom) {
						addingCountry = neighbour;
						validateFortify = false;
					}
				}
			}
		}
	}
	int val;
	while (true) {
		std::cout << "How many do you want to remove from " <<removingCountry->getID()<<"." <<removingCountry->getName() << " (" << removingCountry->getArmies() << " armies)" <<
			"\n\tand add to " <<addingCountry->getID()<< "." <<addingCountry->getName() << " (" << addingCountry->getArmies() << " armies)"<< std::endl;
		std::cin >> val;
		if (removingCountry->getArmies() - val> 0 && val >0) {
			removingCountry->addArmy(removingCountry->getArmies() - val);
			addingCountry->addArmy(addingCountry->getArmies() + val);
			break;
		}
		std::cout << "Your input is incorrect, try again" << std::endl;
	}
	std::cout << "Your armies successfully moved!" << std::endl;
	std::cout << removingCountry->getName() << "(" << removingCountry->getID() << ") has " << removingCountry->getArmies() << " armies" << std::endl;
	std::cout << addingCountry->getName() << "(" << addingCountry->getID() << ") has " << addingCountry->getArmies() << " armies" << std::endl;

	std::cout << "Finished fortification phase" << std::endl;
}