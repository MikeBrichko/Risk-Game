//#include "Player.h"
//#include <iostream>
//
//int main() {
//	std::cout << "Creating a player" << std::endl;
//	Player* player = new Player(1, "Player 1");
//	std::cout << std::endl;
//
//	//Validate Countries in player object
//	//player->printCountriesOwned();
//
//	Map* gameMap = new Map(6);
//	Continent* Continent1 = new Continent(1, "continent1", 5);
//	Continent* Continent2 = new Continent(2, "continent2", 5);
//	Continent* Continent3 = new Continent(3, "continent3", 5);
//	//std::cout << "Add Countries that player owns" << std::endl;
//	Country* Canada = new Country(1, "Canada", 1, 1,1);
//	Country* Argentina = new Country(2, "Argentina", 2, 5,1);
//	Country* Spain = new Country(3, "Spain", 3, 5,1);
//	
//
//	player->addCountryOwned(Canada);
//	player->addCountryOwned(Argentina);
//	player->addCountryOwned(Spain);
//	
//	//Create a second player for testing purposes----------------------------------------------------------------------
//	Player* player2 = new Player(2, "Player 2");
//
//	Country* USA = new Country(4, "USA", 1, 5,2);
//	Country* Mexico = new Country(5, "Mexico", 2, 1,2);
//	Country* Brazil = new Country(6, "Brazil", 2, 5,2);
//
//	player2->addCountryOwned(USA);
//	player2->addCountryOwned(Mexico);
//	player2->addCountryOwned(Brazil);
//	//------------------------------------------------------------------------------------------------------------------
//	
//	//Assign neighbours for each country
//	Canada->addNeighbour(USA);
//	Canada->addNeighbour(Spain);
//	Argentina->addNeighbour(Brazil);
//	Argentina->addNeighbour(Mexico);
//	Spain->addNeighbour(Canada);
//	USA->addNeighbour(Canada);
//	USA->addNeighbour(Mexico);
//	Mexico->addNeighbour(USA);
//	Mexico->addNeighbour(Brazil);
//	Mexico->addNeighbour(Argentina);
//	Brazil->addNeighbour(Mexico);
//	Brazil->addNeighbour(Argentina);
//
//
//	
//	//Validate Fortify
//	player->fortify();
//
//
//
//}