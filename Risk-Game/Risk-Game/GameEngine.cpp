#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <list>
#include <time.h>

GameEngine::GameEngine() {
	map = selectMap();
	players = selectNumberOfPlayers();
}

GameEngine::~GameEngine() {
	delete map;
	for (auto player : *players)
		delete player;
	delete players;
}

Map* GameEngine::selectMap() {
	std::string maps [] = { "brasil.map", "europe.map", "estonia.map", "germany.map", "solar.map" };
	std::cout << "Enter the name of the map you would like to play on: ";
	for (std::string map : maps)
		std::cout << map << ", ";
	std::cout << std::endl;

	std::string selectedMap;
	std::cin >> selectedMap;

	return MapLoader(selectedMap).exportToMap();
}

std::vector<Player*>* GameEngine::selectNumberOfPlayers() {
	int numberOfPlayers = 0;
	std::cout << "Enter the amount of players that will play this game: ";
	std::cin >> numberOfPlayers;
	std::cout << std::endl;

	std::string playerName = "";
	std::vector<Player*>* newPlayers = new std::vector<Player*>();
	for (int i = 0; i < numberOfPlayers; i++) {
		std::cout << "Enter the name of Player " << i + 1 << ": ";
		std::cin >> playerName;
		newPlayers->push_back(new Player(i + 1, playerName));
	}
	return newPlayers;
}

void GameEngine::determinePlayerOrder() {
	int i = 0;
	srand(time(0));
	while (i <= 10) {
		int randomPosition = rand() % players->size();
		Player* player = players->at(randomPosition);
		players->erase(players->begin() + randomPosition);
		players->push_back(player);
		i++;
	}
}

void GameEngine::assignCountriesToPlayers() {
	std::list<Country*> BFSqueue;
	int numVisited = 0;

	//Select Random Continent
	std::vector<Continent*>* continents = map->getContinents();
	Continent* randomContinent = continents->at(rand() % continents->size());

	//Select Random Country
	std::vector<Country*>* countries = randomContinent->getCountries();
	Country* rootCountry = countries->at(rand() % countries->size());
	BFSqueue.push_back(rootCountry);
	numVisited++;

	int playerOrder = 0;
	while (!BFSqueue.empty())
	{
		if (playerOrder == players->size())
			playerOrder = 0;

		rootCountry = BFSqueue.front();
		rootCountry->setVisited(true);

		players->at(playerOrder)->addCountryOwned(rootCountry);
		rootCountry->setPlayerID(players->at(playerOrder)->getPlayerID());
		rootCountry->addArmy(1);
		BFSqueue.pop_front();

		for (auto neighbour : rootCountry->getNeighbours())
		{
			if (!neighbour->getVisited())
			{
				neighbour->setVisited(true);
				numVisited++;
				BFSqueue.push_back(neighbour);
			}
		}
		playerOrder++;
	}

	map->resetVisitedCountries();
}

bool GameEngine::allCountriesHavePlayers() {
	for (int i = 0; i < map->getContinents()->size(); i++) {
		for (int j = 0; j < map->getContinents()->at(i)->getCountries()->size(); j++) {
			if (map->getContinents()->at(i)->getCountries()->at(j)->getPlayerID() == 0)
				return false;
		}
	}
	return true;
}

std::vector<int> GameEngine::totalArmyCountForEachPlayer() {
	std::vector<int> armiesPerPlayer = std::vector<int>();
	int armieCount = 0;
	for (auto player : *players) {
		armieCount = player->armiesOnCountriesOwned();
		std::cout << "Player " << player->getPlayerID() << " has " << armieCount << " armies on the map!" << std::endl;
		armiesPerPlayer.push_back(armieCount);
	}
	return armiesPerPlayer;
}

void GameEngine::startupPhase() {
	determinePlayerOrder();
	assignCountriesToPlayers();

	int givenArmies;
	switch (players->size()) {
		case 2:
			givenArmies = 40;
			break;
		case 3:
			givenArmies = 35;
			break;
		case 4:
			givenArmies = 30;
			break;
		case 5:
			givenArmies = 25;
			break;
		case 6:
			givenArmies = 20;
			break;
		default:
			break;
	}

	std::cout << "Armies on the field before players add armies:" << std::endl;
	std::vector<int> armiesPerPlayer = totalArmyCountForEachPlayer();
	int totalArmiesToBePlaced = 0;
	for (int i = 0; i < players->size(); i++) {
		armiesPerPlayer.at(i) = 20 - armiesPerPlayer.at(i);
		totalArmiesToBePlaced += armiesPerPlayer.at(i);
	}

	std::string countryName;
	int armiesPlacedCounter = 0;
	while (armiesPlacedCounter < totalArmiesToBePlaced) {
		for (int i = 0; i < players->size(); i++) {
			if (armiesPerPlayer.at(i) == 0)
				continue;

			players->at(i)->printCountriesOwned();
			std::cout << "Enter a Country that you would like to add armies to: ";
			std::cin >> countryName;
			//players->at(i)->addArmyToCountry(countryName, 1);

			armiesPerPlayer.at(i)--;
			armiesPlacedCounter++;
		}
	}

	std::cout << "Armies on the field after players add armies:" << std::endl;
	totalArmyCountForEachPlayer();
}

void GameEngine::mainGameLoop() {
	bool gameOver = false;
	while (!gameOver) {
		for (auto player : *players) {
			if (player->getAmountOfCountriesOwned() == 0)
				continue;

			player->reinforce(map);
			player->attack();

			if (player->getAmountOfCountriesOwned() == map->getNumOfCountries()) {
				std::cout << "Player " << player->getPlayerID() << " wins!!!" << std::endl;
				gameOver = true;
				break;
			}

			player->fortifiy();
		}
	}
}
