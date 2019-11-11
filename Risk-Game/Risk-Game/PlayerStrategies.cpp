#include "PlayerStrategies.h"

Strategy::Strategy() {}

//-----------------------------------------------------------------------------------------------------------------------------------------

HumanPlayer::HumanPlayer(){}

void HumanPlayer::reinforce(Player* player) {
	std::cout << "=====================Starting reinforcement phase=====================" << std::endl;
	int armiesToAdd = 0;
	std::cout << "Adding armies based on COUNTRIES that " << player->getPlayerName() << " owns." << std::endl;
	armiesToAdd += floor(player->getCountriesOwned()->size() / 3);

	std::cout << "Adding armies based on CONTINENTS that " << player->getPlayerName() << " owns." << std::endl;
	std::vector<Country* > tempCountriesVector = std::vector<Country*>();
	int comparedID;
	for (auto continent : *player->getGameMap()->getContinents()) {
		for (auto country : *continent->getCountries()) {
			comparedID = country->getID();
			for (auto countryOwned : *player->getCountriesOwned()) {
				if (comparedID == countryOwned->getID()) {
					tempCountriesVector.push_back(countryOwned);
				}
			}
		}
		if (tempCountriesVector.size() == player->getGameMap()->getContinents()->size()) {
			armiesToAdd += continent->getArmyValue();
		}
		tempCountriesVector.clear();
	}

	std::cout << "Adding armies based on CARDS that " << player->getPlayerName() << " owns." << std::endl;
	armiesToAdd += player->addCardToHand();

	player->printCountriesOwned();

	std::string countryOwnedName;
	int armyInput;
	int armiesLeftToAdd = armiesToAdd;
	Country* countryToAddArmiesTo = NULL;
	for (int i = 0; i < armiesToAdd; i++) {
		std::cout << "Armies available to place: " << armiesLeftToAdd << "." << std::endl << std::endl;

		//Step 1. Select Owned Country
		while (true) {
			std::cout << "Please enter the name of the country that you would like to add armies to:" << std::endl;
			std::cin >> countryOwnedName;
			countryToAddArmiesTo = player->getCountryOwned(countryOwnedName);

			if (countryToAddArmiesTo != NULL)
				break;
			else
				std::cout << "Invalid input! You do not own " << countryOwnedName << "." << std::endl;
		}

		//Step 2. Add armies to selected country
		while (true) {
			std::cout << "How many armies would you like to add to " << countryOwnedName << "?" << std::endl;
			std::cin >> armyInput;

			if (armyInput < 0 || (armiesLeftToAdd - armyInput) < 0)
				std::cout << "Invalid input! Please enter a value between 0 and " << armiesLeftToAdd << " inclusively." << std::endl;
			else
				break;
		}

		countryToAddArmiesTo->addArmy(armyInput);
		armiesLeftToAdd -= armyInput;
		i += (armyInput - 1);
	}
	player->printCountriesOwned();
	std::cout << "=====================Finished reinforcement phase=========================" << std::endl;
}

void HumanPlayer::attack(Player* player, std::vector<Player*>* players) {
	std::cout << "=====================Starting Attack Phase=====================" << std::endl;
	std::cout << "For " << player->getPlayerName() << std::endl;
	player->printNeighbours(true);

	std::string attackingCountryName;
	Country* attackingCountry = NULL;
	std::vector<int> attackingDice;

	std::string defendingCountryName;
	Country* defendingCountry = NULL;
	std::vector<int> defendingDice;

	while (player->playerAttackDecision())
	{
		//Step 1: Select the attacking country
		while (true)
		{
			std::cout << "Please enter the name of the country that you would like to attack with: " << std::endl;
			std::cin >> attackingCountryName;
			attackingCountry = player->getCountryOwned(attackingCountryName);

			if (attackingCountry != NULL) {
				if (attackingCountry->getArmies() >= 2)
					break;
				else
					std::cout << "Invalid input! " << attackingCountryName << " has less than 2 armies." << std::endl;
			}
			else
				std::cout << "Invalid input! You do not own " << attackingCountryName << "." << std::endl;
		}

		//Step 2. Select the defending country
		while (true) {
			std::cout << "Please enter the name of the country that you want to attack: " << std::endl;
			std::cin >> defendingCountryName;
			defendingCountry = player->getNeighbouringCountry(attackingCountry, defendingCountryName, true);

			if (defendingCountry != NULL)
				break;
			else
				std::cout << "Invalid input! " << defendingCountryName << " is not an enemy country." << std::endl;
		}

		//Step 3. Roll Dices
		//Attacker Dice Roll
		std::cout << "Attacker rolls" << std::endl;
		attackingDice = player->getGameDice()->rollDice(attackingCountry->getArmies(), true);
		std::cout << "Attacking Player rolled: ";
		for (auto diceFace : attackingDice)
			std::cout << diceFace << " ";
		std::cout << std::endl;

		//Defender Dice Roll
		std::cout << "Defender rolls " << std::endl;
		defendingDice = player->getGameDice()->rollDice(defendingCountry->getArmies(), false);
		std::cout << "Defending Player rolled: ";
		for (auto diceFace : defendingDice)
			std::cout << diceFace << " ";
		std::cout << std::endl;

		//Dice Roll Outcome
		int minimumSize = (attackingDice.size() < defendingDice.size() ? attackingDice.size() : defendingDice.size());
		for (int i = 0; i < minimumSize; i++) {
			if (attackingDice[i] <= defendingDice[i]) {
				attackingCountry->addArmy(-1);

				if (attackingCountry->getArmies() == 1)
					break;
			}
			else {
				defendingCountry->addArmy(-1);
				if (defendingCountry->getArmies() == 0) {
					player->conquerEnemyCountry(attackingCountry, defendingCountry, players);
				}
			}
		}

		player->printNeighbours(true);
	}
	std::cout << "=====================Finished Attack Phase=====================" << std::endl;
}

void HumanPlayer::fortify(Player* player) {
	std::cout << "=====================Starting fortification phase=====================" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	player->printNeighbours(false);

	//Step 1. Select Country having armies removed
	Country* transferingCountry = NULL;
	std::string transferingCountryName;
	while (player->playerFortificationDecision()) {
		while (true)
		{
			std::cout << "Please enter the name of the country that you would like to transfer armies from: " << std::endl;
			std::cin >> transferingCountryName;
			transferingCountry = player->getCountryOwned(transferingCountryName);

			if (transferingCountry != NULL) {
				if (transferingCountry->getArmies() >= 2)
					break;
				else
					std::cout << "Invalid input! " << transferingCountryName << " has less than 2 armies." << std::endl;
			}
			else
				std::cout << "Invalid choice! You do not own " << transferingCountryName << "." << std::endl;
		}

		//Step 2. Select Friendly Neighbour
		Country* receivingCountry = NULL;
		std::string receivingCountryName;
		while (true) {
			std::cout << "Please enter the name of the country that you would like to receive armies: " << std::endl;
			std::cin >> receivingCountryName;
			receivingCountry = player->getNeighbouringCountry(transferingCountry, receivingCountryName, false);

			if (receivingCountry != NULL)
				break;
			else
				std::cout << "Invalid choice! " << receivingCountryName << " is not a friendly neighbour of " << transferingCountryName << "." << std::endl;
		}

		//Step 3. Move armies to friendly Country
		int armiesToMobilize = 0;
		while (true) {
			std::cout << transferingCountryName << " has " << transferingCountry->getArmies() << " armies." << std::endl;
			std::cout << "How many armies would you like to move from " << transferingCountryName << " to " << receivingCountryName << "?" << std::endl;
			std::cin >> armiesToMobilize;

			if (armiesToMobilize <= (transferingCountry->getArmies() - 1) && armiesToMobilize >= 0)
				break;
			else
				std::cout << "Can't move that many armies! Select the amount of armies in between 1 and " << transferingCountry->getArmies() - 1 << std::endl;
		}

		transferingCountry->addArmy(-armiesToMobilize);
		receivingCountry->addArmy(armiesToMobilize);
		break;
	}

	player->printNeighbours(false);
	std::cout << "=====================Finished fortification phase=====================" << std::endl;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

AggressiveComputer::AggressiveComputer(){}

Country* AggressiveComputer::getStrongestCountry(std::vector<Country*>* countriesOwned) {
	Country* strongestCountry = NULL;
	int maxArmies = 0;
	for (auto country : *countriesOwned) {
		if (country->getArmies() > maxArmies)
			strongestCountry = country;
	}
	return strongestCountry;
}

void AggressiveComputer::reinforce(Player* player) {
	std::cout << "=====================Starting reinforcement phase=====================" << std::endl;
	int armiesToAdd = 0;
	std::cout << "Adding armies based on COUNTRIES that " << player->getPlayerName() << " owns." << std::endl;
	armiesToAdd += floor(player->getCountriesOwned()->size() / 3);

	std::cout << "Adding armies based on CONTINENTS that " << player->getPlayerName() << " owns." << std::endl;
	std::vector<Country* > tempCountriesVector = std::vector<Country*>();
	int comparedID;
	for (auto continent : *player->getGameMap()->getContinents()) {
		for (auto country : *continent->getCountries()) {
			comparedID = country->getID();
			for (auto countryOwned : *player->getCountriesOwned()) {
				if (comparedID == countryOwned->getID()) {
					tempCountriesVector.push_back(countryOwned);
				}
			}
		}
		if (tempCountriesVector.size() == player->getGameMap()->getContinents()->size()) {
			armiesToAdd += continent->getArmyValue();
		}
		tempCountriesVector.clear();
	}

	std::cout << "Adding armies based on CARDS that " << player->getPlayerName() << " owns." << std::endl;
	armiesToAdd += player->addCardToHand();

	player->printCountriesOwned();

	Country* strongestCountry = getStrongestCountry(player->getCountriesOwned());
	strongestCountry->addArmy(armiesToAdd);

	player->printCountriesOwned();
	std::cout << "=====================Finished reinforcement phase=========================" << std::endl;
}

void AggressiveComputer::attack(Player* player, std::vector<Player*>* players) {
	std::cout << "=====================Starting Attack Phase=====================" << std::endl;
	std::cout << "For " << player->getPlayerName() << std::endl;
	player->printNeighbours(true);

	//Step 1. Select the attacking country
	Country* strongestCountry = getStrongestCountry(player->getCountriesOwned());

	//Step 2. Select the defending country
	std::vector<int> attackingDice;
	std::vector<int> defendingDice;
	while (true) {
		if (strongestCountry->getArmies() == 1)
			break;

		for (auto neighbourCountry : strongestCountry->getNeighbours()) {
			if (neighbourCountry->getPlayerID() != player->getPlayerID())
				continue;

			attackingDice = player->getGameDice()->rollDice(strongestCountry->getArmies(), true);
			defendingDice = player->getGameDice()->rollDice(neighbourCountry->getArmies(), false);

			int minimumSize = (attackingDice.size() < defendingDice.size() ? attackingDice.size() : defendingDice.size());
			for (int i = 0; i < minimumSize; i++) {
				if (attackingDice[i] <= defendingDice[i]) {
					strongestCountry->addArmy(-1);

					if (strongestCountry->getArmies() == 1)
						break;
				}
				else {
					neighbourCountry->addArmy(-1);
					if (neighbourCountry->getArmies() == 0) {
						player->conquerEnemyCountry(strongestCountry, neighbourCountry, players);
					}
				}
			}
		}
	}

	player->printNeighbours(true);
	
	std::cout << "=====================Finished Attack Phase=====================" << std::endl;
}

void AggressiveComputer::fortify(Player* player) {
	std::cout << "=====================Starting fortification phase=====================" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	player->printNeighbours(false);

	if (player->armiesOnCountriesOwned() == player->getCountriesOwned()->size()) {

		//Step 1. Select Country having armies removed and Friendly Neighbour
		Country* transferingCountry = NULL;
		Country* receivingCountry = NULL;
		int maxArmies = 0;
		for (auto countryOwned : *player->getCountriesOwned()) {
			if (countryOwned->getArmies() <= 1)
				continue;
			for (auto neighbourCountry : countryOwned->getNeighbours()) {
				if (neighbourCountry->getPlayerID() == player->getPlayerID()) {
					if (countryOwned->getArmies() + neighbourCountry->getArmies() > maxArmies) {
						transferingCountry = countryOwned;
						receivingCountry = neighbourCountry;
					}
				}
			}
		}

		//Step 2. Move armies to friendly Country
		int armiesToMobilize = transferingCountry->getArmies() - 1;
		transferingCountry->addArmy(-armiesToMobilize);
		receivingCountry->addArmy(armiesToMobilize);
	}
	player->printNeighbours(false);
	std::cout << "=====================Finished fortification phase=====================" << std::endl;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

BenevolentComputer::BenevolentComputer(){}

Country* BenevolentComputer::getWeakestCountry(std::vector<Country*>* countries) {
	Country* weakestCountry = NULL;
	int minArmies = 1000;
	for (auto country : *countries) {
		if (country->getArmies() < minArmies)
			weakestCountry = country;
	}
	return weakestCountry;
}

void BenevolentComputer::reinforce(Player* player) {
	std::cout << "=====================Starting reinforcement phase=====================" << std::endl;
	int armiesToAdd = 0;
	std::cout << "Adding armies based on COUNTRIES that " << player->getPlayerName() << " owns." << std::endl;
	armiesToAdd += floor(player->getCountriesOwned()->size() / 3);

	std::cout << "Adding armies based on CONTINENTS that " << player->getPlayerName() << " owns." << std::endl;
	std::vector<Country* > tempCountriesVector = std::vector<Country*>();
	int comparedID;
	for (auto continent : *player->getGameMap()->getContinents()) {
		for (auto country : *continent->getCountries()) {
			comparedID = country->getID();
			for (auto countryOwned : *player->getCountriesOwned()) {
				if (comparedID == countryOwned->getID()) {
					tempCountriesVector.push_back(countryOwned);
				}
			}
		}
		if (tempCountriesVector.size() == player->getGameMap()->getContinents()->size()) {
			armiesToAdd += continent->getArmyValue();
		}
		tempCountriesVector.clear();
	}

	std::cout << "Adding armies based on CARDS that " << player->getPlayerName() << " owns." << std::endl;
	armiesToAdd += player->addCardToHand();

	player->printCountriesOwned();

	//Add armies
	for (int i = 0; i < armiesToAdd; i++) {
		getWeakestCountry(player->getCountriesOwned())->addArmy(1);
	}

	player->printCountriesOwned();

	std::cout << "=====================Finished reinforcement phase=========================" << std::endl;
}

void BenevolentComputer::fortify(Player* player) {
	std::cout << "=====================Starting fortification phase=====================" << std::endl;
	std::cout << "Moving armies to different countries" << std::endl;
	player->printNeighbours(false);

	if (player->armiesOnCountriesOwned() == player->getCountriesOwned()->size()) {

		//Step 1. Select Country having armies removed and Friendly Neighbour
		Country* transferingCountry = NULL;
		Country* receivingCountry = NULL;
		int minArmies = 1000;
		for (auto countryOwned : *player->getCountriesOwned()) {
			if (countryOwned->getArmies() <= 1)
				continue;

			for (auto neighbourCountry : countryOwned->getNeighbours()) {
				if (neighbourCountry->getPlayerID() == player->getPlayerID()) {
					if (countryOwned->getArmies() + neighbourCountry->getArmies() < minArmies) {
						transferingCountry = countryOwned;
						receivingCountry = neighbourCountry;
					}
				}
			}
		}

		//Step 2. Move armies to friendly Country
		int armiesToMobilize = transferingCountry->getArmies()/2;
		transferingCountry->addArmy(-armiesToMobilize);
		receivingCountry->addArmy(armiesToMobilize);
	}

	player->printNeighbours(false);
	std::cout << "=====================Finished fortification phase=====================" << std::endl;
}