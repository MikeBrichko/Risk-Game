#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

MapLoader::MapLoader(std::string fileName) {
	this->fileName = new std::string(fileName);
}

MapLoader::~MapLoader() {
	delete fileName;
}

void MapLoader::validateMap() {
	std::string line = "";
	std::cout << "Validating file with name -> " << *fileName << std::endl;
	int* componentCounter = new int();
	std::ifstream inFile;
	inFile.open(*fileName);

	if (!inFile) {
		std::cerr << "Unable to open file " + *fileName;
		exit(1);
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
		else if (line.find("[countries]") == 0) {
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
		else if (line.find("[borders]") == 0) {
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
	}
	else {
		std::cout << "End of file has been reached. Map File is valid" << std::endl;
	}
	delete(componentCounter);
	inFile.close();
}

bool MapLoader::validateContinents(std::string lineToValidate) {
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

bool MapLoader::validateCountries(std::string lineToValidate) {
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

bool MapLoader::validateBorders(std::string lineToValidate) {
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

Map* MapLoader::exportToMap(){
	std::cout << "Creating game map" << std::endl;

	std::ifstream inFile;
	inFile.open(*fileName);

	if (!inFile) {
		std::cerr << "Unable to open file " + *fileName;
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

	Map* map = new Map(countries->size());
	for (auto continent : *continents) {
		map->addContinent(continent);
	}

	std::cout << "End of file has been reached. Map has been created." << std::endl;
    inFile.close(); 

	return map;
}

Continent* MapLoader::createContinent(std::string line, int continentID) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	return new Continent(continentID, words.at(0), stoi(words.at(1)));
}

Country* MapLoader::createCountry(std::string line, std::vector<Continent*>* continents) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();
	Country* createdCountry = new Country(stoi(words.at(0)), words.at(1), stoi(words.at(2)), 0);
	continents->at((double)stoi(words.at(2)) - 1)->addCountry(createdCountry);
	return createdCountry;
}

void MapLoader::createBorders(std::string line, std::vector<Country*>* countries) {
	std::string word;
	std::vector<std::string> words = std::vector<std::string>();
	std::stringstream ss(line);

	while (ss >> word) {
		words.push_back(word);
	}
	ss.clear();

	for (int i = 1; i < words.size(); i++)
		countries->at((double)stoi(words.at(0))-1)->addNeighbour(countries->at((double)stoi(words.at(i))-1));
}
