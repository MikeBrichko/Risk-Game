#pragma once
#include "Player.h"
#include <vector>

class GameEngine {
private:
	Map* map;
	std::vector<Player*>* players;
	Deck* deck;

	//Part 1 & 2
	Map* selectMap();
	std::vector<Player*>* selectNumberOfPlayers();
	void determinePlayerOrder();
	void assignCountriesToPlayers();
	std::vector<int> totalArmyCountForEachPlayer();

	//Part 3
	void removePlayer(int playerID);

public:
	//Part 1 & 2
	GameEngine();
	~GameEngine();
	void startupPhase();
	bool allCountriesHavePlayers();

	//Part 3
	void mainGameLoop();
};