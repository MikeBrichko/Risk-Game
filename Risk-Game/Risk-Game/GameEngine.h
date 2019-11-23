#pragma once
#include "Player.h"
#include <vector>
#include "GameObservers.h"

class GameEngine : public Subject{
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
	Strategy* selectPlayerStrategy();

public:
	GameEngine();
	GameEngine(bool);
	~GameEngine();
	void startupPhase();
	void mainGameLoop();
	bool allCountriesHavePlayers();
	std::vector<ConcreteObserver*>* player_observers;
	void askingUserInput();
};