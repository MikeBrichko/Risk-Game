#include "Player.h"
#include <iostream>

Player::Player(int playerID, std::string playerName) {
	this->playerID = new int(playerID);
	this->playerName = new std::string(playerName);
	countriesOwned = new std::vector<Country*>();
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

void Player::printCountriesOwned() {
	std::cout << "These are the countries " << *playerName << " owns: ";
	for (auto country : *countriesOwned)
		std::cout << country->getName() << " ";
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

void Player::addCardToHand(Card* card) {
	hand->addCard(card);
}

void Player::reinforce() {
	int armieCount = 0;
	std::cout << "Starting reinforcement phase" << std::endl;

	std::cout << "Adding armies based on Countries that " << *playerName << " owns."<< std::endl;
	armieCount += floor(countriesOwned->size()/3);

	std::cout << "Adding armies based on Continents that " << *playerName << " owns." << std::endl;
	//armieCount += continentsOwned();

	std::cout << "Adding armies based on Cards that " << *playerName << " owns." << std::endl;
	//armieCount += addCard();
	//change existin mthod to return a number

	std::cout << "Place Armies." << std::endl;
	printCountriesOwned();
	//loop based on armieCount where there is a addArmy()
	//addArmy() will cmake sure that the player has effectively placed this exact number of 
	//new armies somewhere on the map by the end of the reinforcement phase.

	std::cout << "Finished reinforcement phase" << std::endl;
}

void Player::attack() {

	std::cout << "Starting Attack Phase" << std::endl;
	std::cout << *playerName << " picks what country he attacks" << std::endl;
	//print countries that can be attacked by which country
	//dont print country with less than 2 armies on it
	//Example
	//Country A can attack Country B,C,D
	//Country E can attack F,G
	//etc...

	std::cout << "Player chooses to attack" << std::endl;
	//while loop -> playerAttack() returns boolean
	//select country to attack
	//void attackOutcome(Country* X, Country* Y);
	//within the method above -> void removeArmy(Country*)
	std::cout << "Finished Attack Phase" << std::endl;
}

void Player::fortifiy() {
	std::cout << "Starting fortification phase" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	//if(player want to move armies){
	//Countries that can move armies: 
	//Country A to Country B, C or E
	//Country C to Country A, Country E or Country H
	//moveArmies(Country* X, Country* Y)
	//}
	std::cout << "Finished fortification phase" << std::endl;
}