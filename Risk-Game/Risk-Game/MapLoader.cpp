#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

DominationMapLoader::DominationMapLoader() {
	this->dominationFileName = NULL;
}

DominationMapLoader::DominationMapLoader(std::string dominationFileName) {
	this->dominationFileName = new std::string(dominationFileName);
}

DominationMapLoader::~DominationMapLoader() {
	delete dominationFileName;
}

bool DominationMapLoader::dominationValidateMap() {
	std::string line = "";
	std::cout << "Validating file with name -> " << *dominationFileName << std::endl;
	int* componentCounter = new int();
	std::ifstream inFile;
	inFile.open(*dominationFileName);

	if (!inFile) {
		std::cerr << "Unable to open file " + *dominationFileName;
		return false;
	}

	while (std::getline(inFile, line)) {
		//validate continent objects
		if (line.find("[continents]") == 0) {
			getline(inFile, line);
			while (line.find("[countries]") != 0) {
				if (validateContinents(line)) {
					getline(inFile, line);
				}
				else {
					exit(1);
				}
			}
			++* componentCounter;
		}

		//validate country objects
		if (line.find("[countries]") == 0) {
			getline(inFile, line);
			while (line.find("[borders]") != 0) {
				if (validateCountries(line)) {
					getline(inFile, line);
				}
				else {
					exit(1);
				};
			}
			++* componentCounter;
		}

		//validate borders
		if (line.find("[borders]") == 0) {
			getline(inFile, line);
			while (!line.empty()) {
				if (validateBorders(line)) {
					getline(inFile, line);
				}
				else {
					exit(1);
				};
			}
			++* componentCounter;
		}
	}
	if (*componentCounter < 3) {
		std::cout << "The Map file is invalid. One of the map components is missing." << std::endl;
		delete(componentCounter);
		inFile.close();
		return false;
	}
	else {
		std::cout << "End of file has been reached. Map File is valid" << std::endl;
		delete(componentCounter);
		inFile.close();
		return true;
	}
}

bool DominationMapLoader::validateContinents(std::string lineToValidate) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(lineToValidate); 

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	if (!(words.size() == 3 || words.size() == 0)) {
		std::cout << "Invalid Continent Format" << std::endl;
		return false;
	}

	return true;
}

bool DominationMapLoader::validateCountries(std::string lineToValidate) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(lineToValidate);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	if (!(words.size() == 5 || words.size() == 0)) {
		std::cout << "Invalid Country Format" << std::endl;
		return false;
	}

	return true;
}

bool DominationMapLoader::validateBorders(std::string lineToValidate) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(lineToValidate);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	if (words.size() < 2) {
		std::cout << "Invalid Border Format" << std::endl;
		return false;
	}

	return true;
}

Map* DominationMapLoader::dominationExportToMap(){
	std::cout << "Creating game map" << std::endl;

	std::ifstream inFile;
	inFile.open(*dominationFileName);

	if (!inFile) {
		std::cerr << "Unable to open file " + *dominationFileName;
		exit(1);
	}
    
	std::string line = "";
	int continentID = 1;
	std::vector<Continent*>* continents = new std::vector<Continent*>();
	std::vector<Country*>* countries = new std::vector<Country*>();
	while (getline(inFile, line)) {

		//procedure for continents
		if (line.find("[continents]") == 0) {
			getline(inFile, line);
			std::cout << "Creating Continent Objects" << std::endl;
			while (line.find("[countries]") != 0) {
				if (line == "")
					break;
				continents->push_back(createContinent(line, continentID));
				continentID++;
				getline(inFile, line);
			}

		}
		
		//procedure for countries
		if( line.find("[countries]") == 0){
			getline(inFile, line);
			std::cout<<"Creating Country Objects"<<std::endl;
			while(line.find("[borders]") != 0){
				if (line == "")
					break;
			   countries->push_back(createCountry(line, continents));
			   getline(inFile, line);
			}

		}

		//procedure for borders
		if( line.find("[borders]") == 0){
			getline(inFile, line);
			std::cout<<"Adding Neighbours to Countries"<< std::endl;
			while(!line.empty()){
				if (line == "")
					break;
				createBorders(line, countries);
			   getline(inFile, line);
			}
		}

	} 

	Map* map = new Map(static_cast<int>(countries->size()));
	for (auto continent : *continents) {
		map->addContinent(continent);
	}

	std::cout << "End of file has been reached. Map has been created." << std::endl;
    inFile.close(); 

	return map;
}

Continent* DominationMapLoader::createContinent(std::string line, int continentID) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	return new Continent(continentID, words.at(0), stoi(words.at(1)));
}

Country* DominationMapLoader::createCountry(std::string line, std::vector<Continent*>* continents) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();
	Country* createdCountry = new Country(stoi(words.at(0)), words.at(1), stoi(words.at(2)), 0);
	continents->at(static_cast<unsigned __int64>(stoi(words.at(2)) - 1.0))->addCountry(createdCountry);
	return createdCountry;
}

void DominationMapLoader::createBorders(std::string line, std::vector<Country*>* countries) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	for (int i = 1; i < words.size(); i++)
		countries->at(static_cast<unsigned __int64>(stoi(words.at(0))-1.0))->addNeighbour(countries->at(static_cast<unsigned __int64>(stoi(words.at(i))-1.0)));
}

ConquestMapLoader::ConquestMapLoader() {
	this->conquestFileName = NULL;
}

ConquestMapLoader::ConquestMapLoader(std::string dominationFileName) {
	this->conquestFileName = new std::string(dominationFileName);
}

ConquestMapLoader::~ConquestMapLoader() {
	delete conquestFileName;
}

bool ConquestMapLoader::conquestValidateMap() {
	std::string line = "";
	std::cout << "Validating conquest map file with name -> " << *conquestFileName << std::endl;
	std::ifstream inFile;
	inFile.open(*conquestFileName);

	//check if the file exists
	if (!inFile) {
		std::cerr << "Unable to open file " + *conquestFileName;
		return false;
	}

	//go in the file and check if its a valid map file
	while (getline(inFile, line)) {
		if (line.find("[Continents]") == 0) {
			std::cout << "[continents] found" << std::endl;
			while (line.find("[Territories]") != 0) {
				getline(inFile, line);
				if (conquestValidateContinents(line)) {
					getline(inFile, line);
				}
				else {
					std::cout << "CONTINENT is not valid" << std::endl;
					return false;
				}
			}
		}
		if (line.find("[Territories]") == 0) {
			std::cout << "[territories] found" << std::endl;
			while (!line.empty()) {
				getline(inFile, line);
				if (conquestValidateCountries(line) && conquestValidateBorders(line)) {
					getline(inFile, line);
				}
				else {
					std::cout << "invalid territories" << std::endl;
					return false;
				}
			}
		}
	}

	std::cout << " \n" << *conquestFileName << " is a valid map!" << std::endl;
	inFile.close();
	return true;
}

bool ConquestMapLoader::conquestValidateContinents(std::string lineToValidate) {
	bool equalsFound = false;

	if (lineToValidate.empty()) {
		return true;
	}
	for (int i = 0; i < lineToValidate.size(); i++) {
		if (lineToValidate[i] == '=') {
			equalsFound = true;
			break;
		}
	}
	//if the last character is a digit, it is good
	if (isdigit(lineToValidate.at(lineToValidate.size() - 1)) && equalsFound) {
		return true;
	}
	return false;
}

bool ConquestMapLoader::checkIfNumber(std::string num) {
	for (int i = 0; i < num.size(); i++) {
		if (!isdigit(num.at(i))) {
			std::cout << num << "is not a number" << std::endl;
			return false;
		}
	}
	return true;
}

bool ConquestMapLoader::conquestValidateCountries(std::string lineToValidate) {
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(lineToValidate);
	std::string word;

	while (ss.good()) {
		getline(ss, word, ',');
		words.push_back(word);
	}

	for (int i = 1; i < 3; i++) {
		if (!checkIfNumber(words[1])) {
			return false;
		}
	}

	//std::cout << words[0] << " is a country!" << std::endl;
	return true;
}

bool ConquestMapLoader::conquestValidateBorders(std::string lineToValidate) {
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(lineToValidate);
	std::string word;

	while (ss.good()) {
		getline(ss, word, ',');
		words.push_back(word);
	}

	if (words.size() < 5) {
		return false;
	}
	//std::cout << words[0] << " has valid borders!" << std::endl;
	return true;

}

Map* ConquestMapLoader::conquestExportToMap() {
	std::string line = "";
	int continentID = 1;
	int countryID = 1;
	std::vector<Continent*>* continents = new std::vector<Continent*>();
	std::vector<Country*>* countries = new std::vector<Country*>();
	std::ifstream inFile;

	inFile.open(*conquestFileName);

	std::cout << "map creation start\n" << std::endl;

	//first loop to store /  create the continents and the countries
	while (getline(inFile, line)) {
		if (line.find("[Continents]") == 0) {
			getline(inFile, line);
			std::cout << "===============Creating Continent Objects===================" << std::endl;
			while (line.find("[Territories]") != 0) {
				if (line == "")
					break;
				continents->push_back(conquestCreateContinent(line, continentID));
				continentID++;
				getline(inFile, line);
			}std::cout << "continent Objects Created" << std::endl;
		}

		if (line.find("[Territories]") == 0) {
			getline(inFile, line);
			std::cout << "=================Creating country=====================" << std::endl;
			while (!line.empty()) {
				countries->push_back(conquestCreateCountry(countryID, line, continents));
				countryID++;
				getline(inFile, line);
			}
			std::cout << "country Objects Created" << std::endl;
		}
	}

	inFile.close();

	//another loop to create borders from the countries created in the previous loop
	inFile.open(*conquestFileName);
	while (getline(inFile, line)) {
		if (line.find("[Territories]") == 0) {
			getline(inFile, line);
			std::cout << "====================creating borders===================" << std::endl;
			while (!line.empty()) {
				conquestCreateBorders(line, countries);
				getline(inFile, line);
			}
		}
	}
	std::cout << "border Objects Created" << std::endl;
	inFile.close();


	Map* map = new Map(static_cast<int>(countries->size()));

	for (auto continent : *continents) {
		map->addContinent(continent);
	}

	return map;
}

Continent* ConquestMapLoader::conquestCreateContinent(std::string line, int continentID) {
	std::string continentName = line.substr(0, line.find("="));
	int armyValue = line[line.size() - 1];

	//std::cout << continentName <<" " << armyValue<< std::endl;
	return new Continent(continentID, continentName, armyValue);
}

Country* ConquestMapLoader::conquestCreateCountry(int countryID, std::string line, std::vector<Continent*>* continents) {
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);
	std::string word;
	int continentID = 0;
	std::string continentName;
	//random num in place of armyvalue????
	int num = rand() % 15;
	//======================

	while (ss.good()) {
		getline(ss, word, ',');
		words.push_back(word);
	}
	ss.clear();

	for (auto continent : *continents) {
		if (continent->getName() == words[3]) {
			continentID = continent->getID();
		}
	}

	//BIG MISTAKE HERE: ARMY VALUE FOR COUNTRY NOT DEFINED IN THE CONQUEST MAP?????
	//std::cout << "country "<< countryID <<": "<< words[0] << " " << continentID << " " << num << std::endl;
	Country* createdCountry = new Country(countryID, words[0], continentID, num);
	continents->at(static_cast<__int64>(continentID - 1.0))->addCountry(createdCountry);
	return createdCountry;
}

void ConquestMapLoader::conquestCreateBorders(std::string line, std::vector<Country*>* countries) {
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);
	std::string word;
	Country* currentCountry = NULL;

	while (ss.good()) {
		getline(ss, word, ',');
		words.push_back(word);
	}
	ss.clear();

	//assign the country for which you want to add neighbours

	for (auto country : *countries) {
		if (country->getName() == words[0]) {
			currentCountry = country;
			//std::cout << "current Country " << currentCountry->getName()<<" has neighbours: "  << std::endl;
		}
	}

	//neighbours being added
	for (int i = 4; i < words.size(); i++) {
		for (auto country : *countries) {
			if (country->getName() == words[i]) {
				currentCountry->addNeighbour(country);
				//std::cout << country->getName() << std::endl;
			}
		}
	}
}

TwoWayMapAdapter::TwoWayMapAdapter(DominationMapLoader* newMapLoader) {
	dominationMapLoader = newMapLoader;
	conquestMapLoader = NULL;
}

TwoWayMapAdapter::TwoWayMapAdapter(ConquestMapLoader* newConquestMapLoader) {
	dominationMapLoader = NULL;
	conquestMapLoader = newConquestMapLoader;
}

bool TwoWayMapAdapter::conquestValidateMap() {
	return dominationMapLoader->dominationValidateMap();
}

Map* TwoWayMapAdapter::conquestExportToMap() {
	return dominationMapLoader->dominationExportToMap();
}

bool TwoWayMapAdapter::dominationValidateMap() {
	return conquestMapLoader->conquestValidateMap();
}

Map* TwoWayMapAdapter::dominationExportToMap() {
	return conquestMapLoader->conquestExportToMap();
}