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
	std::string* currentPlayerName;
	Phase* currentPhase;
	void attachObserver(Observer* observer);

	void detachObserver(Observer* observer);

	void notifyObservers();

	void notify(std::string name, Phase phase);
};
class DisplayInfo : public Observer //Similar to DigitalClock.h in notes
{
	//this is class as the Concrete Observer
public:

	//DisplayInfo();
	//~DisplayInfo();
	DisplayInfo(int id);
	void displayStats(std::string name, Phase phase);
	void displayVictory(std::string name, Phase phase);
	//void Update();
	//void display();
private:
	//something
	virtual void update(std::string name, Phase phase) override;
	int id;
};