#include "Player.h"
#include <iostream>

/*int main() {
	std::cout << "Creating Game Map" << std::endl;
	Map* gameMap = new Map(6);
	Continent* Continent1 = new Continent(1, "continent1", 5);
	Continent* Continent2 = new Continent(2, "continent2", 6);
	Continent* Continent3 = new Continent(3, "continent3", 7);

	gameMap->addContinent(Continent1);
	gameMap->addContinent(Continent2);
	gameMap->addContinent(Continent3);

	Country* Canada = new Country(1, "Canada", 1, 5);
	Country* Argentina = new Country(2, "Argentina", 2, 5);
	Country* Spain = new Country(3, "Spain", 3, 5);
	Country* USA = new Country(4, "USA", 1, 5);
	Country* Mexico = new Country(5, "Mexico", 2, 5);
	Country* Brazil = new Country(6, "Brazil", 2, 5);

	Continent1->addCountry(Canada);
	Continent1->addCountry(USA);

	Continent2->addCountry(Brazil);
	Continent2->addCountry(Argentina);
	Continent2->addCountry(Mexico);

	Continent3->addCountry(Spain);

	Canada->addNeighbour(USA);
	Canada->addNeighbour(Spain);
	Argentina->addNeighbour(Brazil);
	Argentina->addNeighbour(Mexico);
	Spain->addNeighbour(Canada);
	USA->addNeighbour(Canada);
	USA->addNeighbour(Mexico);
	Mexico->addNeighbour(USA);
	Mexico->addNeighbour(Brazil);
	Mexico->addNeighbour(Argentina);
	Brazil->addNeighbour(Mexico);
	Brazil->addNeighbour(Argentina);

	std::cout << "Creating a player" << std::endl;
	Deck* deck = new Deck(gameMap->getNumOfCountries());
	Dice* dice = new Dice();
	Player * player = new Player(1, "Player 1", deck, gameMap, dice);
	std::cout << std::endl;

	player->addCountryOwned(Canada);
	player->addCountryOwned(Mexico);
	player->addCountryOwned(Argentina);
	player->addCountryOwned(Brazil);

	//Validate Cards in Hand
	player->printCardsInHand();

	std::cout << "Add cards to players hand" << std::endl;
	player->addCardToHand();
	player->addCardToHand();

	player->printCardsInHand();
	std::cout << std::endl;

	//Valdate Reinforce
	player->printCountriesOwned();
	player->reinforce();
	player->printCountriesOwned();
}*/