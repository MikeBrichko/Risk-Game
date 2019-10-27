#include "Player.h"
#include <iostream>

int main() {
	std::cout << "Creating a player" << std::endl;
	Player* player = new Player(1, "Player 1");
	std::cout << std::endl;

	//Validate Countries in player object
	player->printCountriesOwned();

	std::cout << "Add Countries that player owns" << std::endl;
	Map* map = new Map(4);
	Continent* Continent1 = new Continent(1, "continent1", 5);
	Continent* Continent2 = new Continent(2, "continent2", 5);
	map->addContinent(Continent1);
	map->addContinent(Continent2);

	Country* A = new Country(1, "A", Continent1->getID(), 0);
	Country* B = new Country(1, "B", Continent1->getID(), 0);
	Country* C = new Country(1, "C", Continent2->getID(), 0);
	Country* D = new Country(1, "D", Continent2->getID(), 0);
	Continent1->addCountry(A);
	Continent1->addCountry(B);
	Continent2->addCountry(C);
	Continent2->addCountry(D);

	A->addNeighbour(B);
	A->addNeighbour(C);
	B->addNeighbour(A);
	B->addNeighbour(D);
	C->addNeighbour(A);
	C->addNeighbour(D);
	D->addNeighbour(B);
	D->addNeighbour(C);
	player->addCountryOwned(A);
	player->addCountryOwned(B);
	player->addCountryOwned(C);
	player->addCountryOwned(D);

	std::cout << "print country owned" << std::endl;
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