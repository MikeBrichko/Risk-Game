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
	
	// Used for Observer
	//void notify();
	void getCurrentStatus(Player *, Phase);
public:
	GameEngine();
	~GameEngine();
	void startupPhase();
	void mainGameLoop();
	bool allCountriesHavePlayers();

	// Used for Observer
	Player* currentPlayer;
	Phase* currentPhase;

};

class GamePhase : public Observer {
private:
	GameEngine* game;
	void displayVictory(Player* player, Phase current_phase);
	void displayStats(Player* player, Phase current_phase);
public:
	GamePhase(GameEngine* player);
	~GamePhase();
	void update() override;
};