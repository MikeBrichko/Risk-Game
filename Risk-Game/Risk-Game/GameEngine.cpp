#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <list>
#include <time.h>

void callback(ConcreteSubject* player) {
	switch (player->getPhase()) {
	case Phase::ATTACK:
		std::cout << "********** " << player->getCurrentPlayerName() << " : ATTACK PHASE  **********(From Observer)" << std::endl;
		break;
	case Phase::REINFORCE:
		std::cout << "********** " << player->getCurrentPlayerName() << " : REINFORCE PHASE  **********(From Observer)" << std::endl;
		break;
	case Phase::FORTIFY:
		std::cout << "********** " << player->getCurrentPlayerName() << " : FORTIFY PHASE  **********(From Observer)" << std::endl;
		break;
	case Phase::GAME_OVER:
		std::cout << "********** " << player->getCurrentPlayerName() << " WINS! GAME OVER! **********(From Observer)" << std::endl;
		break;
	case Phase::LOSE_COUNTRY:
		std::cout << "********** " << player->getCurrentPlayerName() << " LOSES " << player->getDefeatedCountryName() << " country **********(From Observer)" << std::endl;
		std::cout << "\n********** PLAYERS WORLD DOMINATION VIEW **********" << std::endl;
		for (auto text : player->getStats()) {
			std::cout << *text << std::endl;
		}
		break;
	case Phase::DEFEATED:
		std::cout << "********** " << player->getCurrentPlayerName() << " LOSES and cannot play anymore,  **********(From Observer)" << std::endl;
		break;
	default:
		std::cout << "********** " << player->getCurrentPlayerName() << " : UNDEFINED PHASE  **********(From Observer)" << std::endl;
	}
}

GameEngine::GameEngine(bool automate) {
	if (automate) {
		player_observers = new std::vector<ConcreteObserver*>();

		map = DominationMapLoader("sample.map").dominationExportToMap();

		deck = new Deck(map->getNumOfCountries());
		dice = new Dice();
		players = new std::vector<Player*>();
		Player* p1 = new Player(1, "Player 1 - Ted", deck, map, dice);
		Player* p2 = new Player(2, "Player 2 - Maria", deck, map, dice);
		players->push_back(p1);
		players->push_back(p2);
		ConcreteObserver* observer1 = new ConcreteObserver(p1, &callback);
		ConcreteObserver* observer2 = new ConcreteObserver(p2, &callback);

		player_observers->emplace_back(observer1);
		player_observers->emplace_back(observer2);

		determinePlayerOrder();
		assignCountriesToPlayers();
		validateAllCountriesHavePlayers();
	}
	else {
		player_observers = new std::vector<ConcreteObserver*>();
		map = selectMap();
		deck = new Deck(map->getNumOfCountries());
		dice = new Dice();
		players = selectNumberOfPlayers();

	}
}

GameEngine::GameEngine() {
	map = selectMap();
	deck = new Deck(map->getNumOfCountries());
	dice = new Dice();
	players = selectNumberOfPlayers();
}

GameEngine::~GameEngine() {
	delete map;
	for (auto player : *players)
		delete player;
	delete players;
	delete deck;
}

Map* GameEngine::selectMap() {
	while (true) {
		std::string maps[] = { "brasil.map", "europe.map", "estonia.map", "germany.map", "solar.map" };
		std::cout << "Enter the name of the map you would like to play on: ";
		for (std::string map : maps)
			std::cout << map << ", ";
		std::cout << std::endl;

		std::string selectedMap;
		std::cin >> selectedMap;

		if (DominationMapLoader(selectedMap).dominationValidateMap()) {
			return DominationMapLoader(selectedMap).dominationExportToMap();
		}
	}
}

Strategy* GameEngine::selectPlayerStrategy() {
	int playerStrategy = 0;
	while (true) {
		std::cout << "Enter:" << std::endl;
		std::cout << "\t1 if you to play as a Human" << std::endl;
		std::cout << "\t2 if you want to play as an Aggressive Computer" << std::endl;
		std::cout << "\t3 if you want to play as a Bnevolent Computer" << std::endl;
		std::cin >> playerStrategy;

		if (playerStrategy == 1)
			return new HumanPlayer();
		else if (playerStrategy == 2)
			return new AggressiveComputer();
		else if (playerStrategy == 3)
			return new BenevolentComputer();
		else
			std::cout << "Invalid input! That is not a valid player strategy." << std::endl;
	}
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
		newPlayers->push_back(new Player(i + 1, playerName,deck, map, dice, selectPlayerStrategy()));
	}
	return newPlayers;
}

void GameEngine::determinePlayerOrder() {
	int i = 0;
	srand((unsigned int)time(NULL));
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

void GameEngine::validateAllCountriesHavePlayers() {
	std::list<Country*> BFSqueue;
	int numVisited = 0;

	//Start BFS algorithm by visiting a random country
	Country* rootCountry = map->getContinents()->at(0)->getCountries()->at(0);
	BFSqueue.push_back(rootCountry);
	if (rootCountry->getPlayerID() != 0)
		numVisited++;

	while (!BFSqueue.empty())
	{
		// Dequeue a vertex from BFSqueue and print it 
		rootCountry = BFSqueue.front();
		rootCountry->setVisited(true);
		BFSqueue.pop_front();

		//Visit all unvisited neighbouring countries and add them to the BFSqueue
		for (auto neighbour : rootCountry->getNeighbours())
		{
			if (!neighbour->getVisited())
			{
				neighbour->setVisited(true);
				if (neighbour->getPlayerID() != 0)
					numVisited++;
				BFSqueue.push_back(neighbour);
			}
		}
	}

	if (numVisited < map->getNumOfCountries())
		std::cout << "Some countries do not have a player :(" << std::endl << std::endl;
	else
		std::cout << "All countries have players :)" << std::endl << std::endl;

	map->resetVisitedCountries();
}

void GameEngine::startupPhase() {
	determinePlayerOrder();
	assignCountriesToPlayers();
	validateAllCountriesHavePlayers();

	int givenArmies = 9;
	/*switch (players->size()) {
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
	}*/

	std::cout << "Armies on the field before players add armies:" << std::endl;
	std::vector<int> armiesPerPlayer = totalArmyCountForEachPlayer();
	int totalArmiesToBePlaced = 0;
	for (int i = 0; i < players->size(); i++) {
		armiesPerPlayer.at(i) = givenArmies - armiesPerPlayer.at(i);
		totalArmiesToBePlaced += armiesPerPlayer.at(i);
	}

	std::string countryName;
	int armiesPlacedCounter = 0;
	Country* countryToBeAddedArmiesTo = NULL;
	while (armiesPlacedCounter < totalArmiesToBePlaced) {
		for (int i = 0; i < players->size(); i++) {
			if (armiesPerPlayer.at(i) == 0)
				continue;

			while (true) {
				players->at(i)->printCountriesOwned();
				std::cout << "Enter a Country that you would like to add armies to: ";
				std::cin >> countryName;

				countryToBeAddedArmiesTo = players->at(i)->getCountryOwned(countryName);
				if (countryToBeAddedArmiesTo != NULL) {
					countryToBeAddedArmiesTo->addArmy(1);
					std::cout << std::endl;
					break;
				}
				else {
					std::cout << "Invalid input! You do not own " << countryName << "." << std::endl;
				}
			}

			armiesPerPlayer.at(i)--;
			armiesPlacedCounter++;
		}
	}

	std::cout << "Armies on the field after players add armies:" << std::endl;
	armiesPerPlayer = totalArmyCountForEachPlayer();
}

void GameEngine::mainGameLoop() {
	bool gameOver = false;
	while (!gameOver) {
		for (auto player : *players) {
			if (player->getAmountOfCountriesOwned() == 0)
				continue;

			player->reinforce();
			player->attack(players);

			if (player->getAmountOfCountriesOwned() == map->getNumOfCountries()) {
				std::cout << "Player " << player->getPlayerID() << " wins!!!" << std::endl;
				gameOver = true;
				break;
			}

			player->fortify();
		}
	}
}