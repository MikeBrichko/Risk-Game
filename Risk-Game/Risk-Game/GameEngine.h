#pragma once
#include "Player.h"
#include <vector>

class GameEngine {
private:
	Map* map;
	std::vector<Player*>* players;

	Map* selectMap();
	std::vector<Player*>* selectNumberOfPlayers();
	void determinePlayerOrder();
	void assignCountriesToPlayers();
	std::vector<int> totalArmyCountForEachPlayer();

public:
	GameEngine();
	~GameEngine();
	void startupPhase();
	void mainGameLoop();
	bool allCountriesHavePlayers();
};