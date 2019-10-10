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

void Player::rollDice(int numberOfCountries) {
	std::vector<int> diceRolled = dice->rollDice(numberOfCountries);
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
	//armieCount += exchange();

	std::cout << "Finished reinforcement phase" << std::endl;
}

void Player::attack() {

	std::cout << "Starting Attack Phase" << std::endl;
	std::cout << *playerName << " picks what country he attacks" << std::endl;
	std::cout << *playerName << " rolls dice to see if attack was succesfull" << std::endl;
	rollDice(60);
	std::cout << "Finished Attack Phase" << std::endl;
}

void Player::fortifiy() {
	std::cout << "Starting fortification phase" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	std::cout << "Finished fortification phase" << std::endl;
}