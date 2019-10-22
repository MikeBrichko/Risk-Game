#pragma once
#include "Player.h"
#include <vector>

class GameEngine {
private:
	Map* map;
	std::vector<Player*>* players;
	Deck* deck;

	//Part 1 & 2
	Map* selectMap(); //predetermmined list of maps
	std::vector<Player*>* selectNumberOfPlayers();
	void determinePlayerOrder(); //sort players vector
	void assignCountriesToPlayers();

	//Part 3
	bool removePlayer(int playerID);

public:
	//Part 1 & 2
	GameEngine();
	~GameEngine();
	bool allCountriesHavePlayers();
	bool validateArmiesOnCountry(int playerID);

	//Part 3
	void mainGameLoop();
};