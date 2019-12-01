#include "GameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <list>
#include <time.h>


//callback function used to display appropriate message in the Observer Pattern
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
	//If the game is to be automated 
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
	//The case when the game is not to be automated
	else {
		player_observers = new std::vector<ConcreteObserver*>();
		map = selectMap();
		deck = new Deck(map->getNumOfCountries());
		dice = new Dice();
		players = selectNumberOfPlayers();

	}
}
GameEngine::GameEngine(std::string tournament) {
	//If GameEngine has tournament as parameter we run the tournament process
	if (tournament == "tournament") {
		players =new std::vector<Player*>();
		tournamentProcess();
	}
	//If GameEngine does not have tournament as parameter we do not run the tournament process
	else {
		map = selectMap();
		deck = new Deck(map->getNumOfCountries());
		dice = new Dice();
		players = selectNumberOfPlayers();
	}
};

//Default GameEngine Process
GameEngine::GameEngine() {
	map = selectMap();
	deck = new Deck(map->getNumOfCountries());
	dice = new Dice();
	players = selectNumberOfPlayers();
}

//Destructor for GameEngine 
GameEngine::~GameEngine() {
	delete map;
	for (auto player : *players)
		delete player;
	delete players;
	delete deck;
}

//Function to get map choice from user and then validate the users input
Map* GameEngine::selectMap() {
	while (true) {
		std::string maps[] = { "brasil.map", "europe.map", "estonia.map", "germany.map", "solar.map" };
		std::cout << "Enter the name of the map you would like to play on: ";
		for (std::string map : maps)
			std::cout << map << ", ";
		std::cout << std::endl;

		std::string selectedMap;
		std::cin >> selectedMap;

		//validate the users input
		if (DominationMapLoader(selectedMap).dominationValidateMap()) {
			return DominationMapLoader(selectedMap).dominationExportToMap();
		}
	}
}

//Function asks user to select a stratgey of their choice for a given player
Strategy* GameEngine::selectPlayerStrategy() {
	int playerStrategy = 0;
	while (true) {
		std::cout << "Enter:" << std::endl;
		std::cout << "\t1 if you to play as a Human" << std::endl;
		std::cout << "\t2 if you want to play as an Aggressive Computer" << std::endl;
		std::cout << "\t3 if you want to play as a Bnevolent Computer" << std::endl;
		std::cout << "\t4 if you want to play as a Random Computer" << std::endl;
		std::cout << "\t5 if you want to play as a Cheater Computer" << std::endl;
		std::cin >> playerStrategy;

		//Check user input and assign appropriate strategy
		if (playerStrategy == 1)
			return new HumanPlayer();
		else if (playerStrategy == 2)
			return new AggressiveComputer();
		else if (playerStrategy == 3)
			return new BenevolentComputer();
		else if (playerStrategy == 4)
			return new RandomComputer(); 
		else if (playerStrategy == 5)
			return new CheaterComputer(); 
		else
			std::cout << "Invalid input! That is not a valid player strategy." << std::endl;
	}
}

//Funciton that asks user to select a strategy of their choice for the computer player
Strategy* GameEngine::selectComputerPlayerStrategy() {
	int playerStrategy = 0;
	while (true) {
		std::cout << "Enter:" << std::endl;
		std::cout << "\t1 if you want to play as an Aggressive Computer" << std::endl;
		std::cout << "\t2 if you want to play as a Bnevolent Computer" << std::endl;
		std::cout << "\t3 if you want to play as a Random Computer" << std::endl;
		std::cout << "\t4 if you want to play as a Cheater Computer" << std::endl;

		std::cin >> playerStrategy;

		//Check user input and assign appropriate strategy
		if (playerStrategy == 1)
			return new AggressiveComputer();
		else if (playerStrategy == 2)
			return new BenevolentComputer();
		else if (playerStrategy == 3)
			return new RandomComputer(); 
		else if (playerStrategy == 4)
			return new CheaterComputer(); 
		else
			std::cout << "Invalid input! That is not a valid player strategy." << std::endl;
	}
}

//Function that asks user the number of player to be played
std::vector<Player*>* GameEngine::selectNumberOfPlayers() {
	int numberOfPlayers = 0;
	std::cout << "Enter the amount of players that will play this game: ";
	std::cin >> numberOfPlayers;
	std::cout << std::endl;

	//Ask the user to name the given player
	std::string playerName = "";
	std::vector<Player*>* newPlayers = new std::vector<Player*>();
	for (int i = 0; i < numberOfPlayers; i++) {
		std::cout << "Enter the name of Player " << i + 1 << ": ";
		std::cin >> playerName;
		newPlayers->push_back(new Player(i + 1, playerName,deck, map, dice, selectPlayerStrategy()));
	}
	return newPlayers;
}

//Function to randomly determine the player order
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

//Function that assigns random countries to player
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

//Fucntion to check that all countries have players
bool GameEngine::allCountriesHavePlayers() {
	for (int i = 0; i < map->getContinents()->size(); i++) {
		for (int j = 0; j < map->getContinents()->at(i)->getCountries()->size(); j++) {
			if (map->getContinents()->at(i)->getCountries()->at(j)->getPlayerID() == 0)
				return false;
		}
	}
	return true;
}

//Function that gives the total amount of armies for each player
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

//Function that checks if every country has a player
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

//The startup phase for the default game
void GameEngine::startupPhase() {
	determinePlayerOrder();
	assignCountriesToPlayers();
	validateAllCountriesHavePlayers();

	int givenArmies = 9;

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
				//display countries that are owned by the current player
				players->at(i)->printCountriesOwned();
				std::cout << "Enter a Country that you would like to add armies to: ";
				std::cin >> countryName;

				//check if user choice a valid country
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

//Main game loop of the Game Engine
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

//Tournament process if the tournament mode is chosen
void GameEngine::tournamentProcess() {
	int gameType;
	int mapNum;
	std::vector<int> mapList;
	int numplayers;
	int numGames;
	int numTurns;

	//single player or tournament
	std::cout << "Which mode to play? Enter '1' for single player or '2' for Tournament Mode" << std::endl;
	std::cin >> gameType;
	while (std::cin.fail() || (gameType <1 ||  gameType >2))
	{
		std::cin.clear();
		std::cin.ignore(1);
		std::cout << "input 1 or 2" << std:: endl;
		std::cin >> gameType;
	}

	if (gameType == 2) {
		//map selection 
		std::cout << "choose how many maps you want to have in tournament [1,5] integer: \n" << std::endl;
		std::cin >> mapNum; 

		//Create a vector to display names of all the maps
		std::vector<std::string> vec{ "1. Alberta", "2. Estonia", "3. Europe", "4. Germany", "5. Solar" };

		int goodMapCounter = 0;
		int chosen = 10;

		//create temporary vector to store chosen map numbers
		std::vector<int> chosenVec;
		
		while (mapNum != goodMapCounter)
		{
			int tempMapNum;
			std::cout << "choose your map from list below (enter number): \n" << std::endl;
			for (int i = 0; i < vec.size(); i++)
			{
				//if map has been chosen we don't display it
				if (i == chosen) 
				{ 
					vec.at(i) = " ";
					continue;
				}
				std::cout << vec.at(i);    
				std::cout << std::endl;
			}
			//receive input from user
			std::cin >> tempMapNum;

			//check if input is between 1 and 5
			if (tempMapNum > 5 || tempMapNum < 1) {
				std::cout << "invalid input, please input an integer from the list of countries" << std::endl;
			}
			//check if input was already chosen before
			else if (std::find(chosenVec.begin(), chosenVec.end(), (tempMapNum - 1)) != chosenVec.end())
			{
				std::cout << "\nYou have already chosen this map number, please input an integer from list of countries" <<std::endl;
				continue;
			}
			//if reach here then the map number is good
			else {
				mapList.push_back(tempMapNum);		//add map number to official map list
				goodMapCounter++;					//increment goodMapCounter
				chosen = tempMapNum - 1;			//initialize chosen to new map number
				chosenVec.push_back(chosen);		//add map number to list of chosen map numbers
			}
		}

		//number of players
		std::cout << "number of players? [2,4] " << std::endl;
		std::cin >> numplayers;
		while (numplayers < 2 || numplayers > 4) {
			std::cout << "input any integer [2,4]" << std::endl;
			std::cin >> numplayers;;
		}
		std::string playerName = "";
		for (int i = 0; i < numplayers; i++) {
			std::cout << "Enter the name of Player " << i + 1 << ": ";
			std::cin >> playerName;
			players->push_back(new Player(i + 1, playerName, deck, map, dice, selectComputerPlayerStrategy()));
		}

		//number of games on each map
		std::cout << "number of games on each map? [1,5] " << std::endl;
		std::cin >> numGames;
		while (numGames < 1 ||  numGames > 5) {
			std::cout << "input any integer [1,5]" << std::endl;
			std::cin >> numGames;
		}

		//num of turns for it to be considered a draw
		std::cout << "number of turns (integer) to be considered a draw [3,50]?";
		std::cin >> numTurns;

		while (numTurns < 3 || numTurns>50) {
			std::cout << "INTEGER" << std::endl;
			std::cin >> numTurns;
		}

		std::cout << "number used will be " << numTurns << std::endl;
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < mapNum; i++) {
			switch (mapList.at(i)) {
			case 1:
				map = ConquestMapLoader("Alberta.map").conquestExportToMap();
				result.push_back("Alberta.map");
				break;
			case 2:
				map = DominationMapLoader("estonia.map").dominationExportToMap();
				result.push_back("estonia.map");
				break;
			case 3:
				map = DominationMapLoader("europe.map").dominationExportToMap();
				result.push_back("europe.map");
				break;
			case 4:
				map = DominationMapLoader("germany.map").dominationExportToMap();
				result.push_back("germany.map");
				break;
			case 5:
				map = DominationMapLoader("solar.map").dominationExportToMap();
				result.push_back("solar.map");
				break;
			}

			deck = new Deck(map->getNumOfCountries());
			dice = new Dice();
			for (auto player : *players) {
				player->setMap(map);
				player->setDice(dice);
				player->setDeck(deck);
			}
			bool gameOver = false;
			//Assign a map logic here, when next for loop is done, new map should be assigned 
			for (int j = 0; j < numGames; j++) {
				determinePlayerOrder();
				assignCountriesToPlayers();
				validateAllCountriesHavePlayers();
				// Game operation here
				gameOver = false;
				for (int k =0; k <numTurns; k++) {
					for (auto player : *players) {
						if (player->getAmountOfCountriesOwned() == 0)
							continue;

						player->reinforce();
						player->attack(players);

						if (player->getAmountOfCountriesOwned() == map->getNumOfCountries()) {
							std::cout << "Player " << player->getPlayerID() << " wins!!!" << std::endl;
							gameOver = true;
							result.at(i) += "\t" + player->getPlayerName();
							break;
						}
						player->fortify();
					}
					if (gameOver) {
						break;
					}
				}
				if (!gameOver) {
					result.at(i) += "\tDraw";
				}
			}
		}
		for (auto resultString : result) {
			std::cout << resultString << std::endl;
		}
		std::string breakpoint;
		std::cin >> breakpoint;
	}
	else {
		//default game loop
		map = selectMap();
		deck = new Deck(map->getNumOfCountries());
		dice = new Dice();
		players = selectNumberOfPlayers();
		startupPhase();
		mainGameLoop();
	}

}