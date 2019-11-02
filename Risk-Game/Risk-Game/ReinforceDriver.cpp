#include "Player.h"
#include <iostream>


int main() {
	std::cout << "Creating a player" << std::endl;
	Player* player = new Player(1, "Player 1");
	std::cout << std::endl;

	//Validate Countries in player object
	//player->printCountriesOwned();

	Map* gameMap = new Map(6);
	Continent* Continent1 = new Continent(1, "continent1", 5);
	Continent* Continent2 = new Continent(2, "continent2", 6);
	Continent* Continent3 = new Continent(3, "continent3", 7);

	//access continents through player
	gameMap->addContinent(Continent1);
	gameMap->addContinent(Continent2);
	gameMap->addContinent(Continent3);

	//std::cout << "Add Countries that player owns" << std::endl;
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

	player->addCountryOwned(Canada);
	player->addCountryOwned(Mexico);
	player->addCountryOwned(Argentina);
	player->addCountryOwned(Brazil);

	



	//Assign neighbours for each country
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



	//Validate Cards in Hand
	player->printCarsInHand();

	std::cout << "Add cards to players hand" << std::endl;
	Card* card1 = new Card(new CardType(infantry));
	Card* card2 = new Card(new CardType(cavalry));
	//player->addCardToHand(card1);
	//player->addCardToHand(card2);

	player->printCarsInHand();
	std::cout << std::endl;

	//Valdate Reinforce
	player->reinforce(gameMap);
	std::cout << std::endl;

	//Validate Attack
	//player->attack();
	std::cout << std::endl;

	//Validate Fortify
	//player->fortify();



}