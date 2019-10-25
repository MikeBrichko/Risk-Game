#include "Player.h"
#include <iostream>

int main() {
	std::cout << "Creating a player" << std::endl;
	Player* player = new Player(1, "Player 1");
	std::cout << std::endl;

	//Validate Countries in player object
	player->printCountriesOwned();

	std::cout << "Add Countries that player owns" << std::endl;
	Country* Alaska = new Country(1, "Alaska", 1, 5);
	Country* Quebec = new Country(2, "Quebec", 1, 5);
	Map* gameMap = new Map(2);
	//player->addCountryOwned(Alaska);
	//player->addCountryOwned(Quebec);

	player->printCountriesOwned();
	std::cout << std::endl;

	//Validate Cards in Hand
	player->printCarsInHand();

	std::cout << "Add cards to players hand" << std::endl;
	Card* card1 = new Card(new CardType(infantry));
	Card* card2 = new Card(new CardType(cavalry));
	player->addCardToHand(card1);
	player->addCardToHand(card2);
	
	player->printCarsInHand();
	std::cout << std::endl;

	//Valdate Reinforce
	//player->reinforce();
	std::cout << std::endl;

	//Validate Attack
	player->attack();
	std::cout << std::endl;

	//Validate Fortify
	//player->fortifiy();
}