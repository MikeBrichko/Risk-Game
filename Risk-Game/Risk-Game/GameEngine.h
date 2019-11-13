#pragma once
#include "Player.h"
#include "GameObservers.h"
#include <vector>

class GameEngine : public Subject {
private:
	Map* map;
	std::vector<Player*>* players;
	Deck* deck;
	Dice* dice;

	Map* selectMap();
	std::vector<Player*>* selectNumberOfPlayers();
	void determinePlayerOrder();
	void assignCountriesToPlayers();
	std::vector<int> totalArmyCountForEachPlayer();
	void validateAllCountriesHavePlayers();

public:
	GameEngine();
	GameEngine(bool);
	~GameEngine();
	void startupPhase();
	void mainGameLoop();
	bool allCountriesHavePlayers();

	// Used for Observer
	std::vector<ConcreteObserver*>* player_observers;

};