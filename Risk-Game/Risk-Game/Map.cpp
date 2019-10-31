#pragma once
#include "Map.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------------------
Country::Country(int countryID, std::string countryName, int countryContinentID, int countryArmies)
{
	ID = new int(countryID);
	name = new std::string(countryName);
	continentID = new int(countryContinentID);
	playerID = new int(0);
	armies = new int(countryArmies);
	visited = new bool(false);
	neighbours = new std::vector<Country*>();
}

Country::Country(int countryID, std::string countryName, int countryContinentID, int countryArmies, int id)
{
	ID = new int(countryID);
	name = new std::string(countryName);
	continentID = new int(countryContinentID);
	playerID = new int(id);
	armies = new int(countryArmies);
	visited = new bool(false);
	neighbours = new std::vector<Country*>();
}
Country::~Country() {
	delete ID;
	delete name;
	delete continentID;
	delete armies;
	delete playerID;
	for (auto neighbour : *neighbours)
		delete neighbour;
	delete neighbours;
}

void Country::addNeighbour(Country* country) {
	neighbours->push_back(country);
}

int Country::getID() {
	return *ID;
}

std::string Country::getName() {
	return *name;
}

std::vector<Country*> Country::getNeighbours(){
	return *neighbours;
}

int Country::getContinentID() {
	return *continentID;
}

int Country::getArmies() {
	return *armies;
}

bool Country::getVisited() {
	return *visited;
}

void Country::setVisited(bool countryVisited) {
	*visited = countryVisited;
}

int Country::getPlayerID() {
	return *playerID;
}

void Country::setPlayerID(int newPlayerID) {
	*playerID = newPlayerID;
}

void Country::addArmy(int numberOfArmies) {
	*armies = numberOfArmies;
}

//----------------------------------------------------------------------------------------------------------------------------------
Continent::Continent(int continentID, std::string continentName, int continentArmyValue) {
	ID = new int(continentID);
	name = new std::string(continentName);
	armyValue = new int(continentArmyValue);
	countries = new std::vector<Country*>();
}

Continent::~Continent() {
	delete ID;
	delete name;
	delete armyValue;
	for (auto country : *countries)
		delete country;
	delete countries;
}

void Continent::addCountry(Country* country) {
	countries->push_back(country);
}

std::vector<Country*>* Continent::getCountries() {
	return countries;
}

std::string Continent::getName() {
	return *name;
}

int Continent::getID() {
	return *ID;
}

//-----------------------------------------------------------------------------------------------------------------------------------
Map::Map(int amountOfCountries)
{
	numOfCountries = new int(amountOfCountries);
	continents = new std::vector<Continent*>();
}               

Map::~Map() {
	delete numOfCountries;
	for (auto continent : *continents)
		delete continent;
	delete continents;
}

void Map::addContinent(Continent* continent) {
	continents->push_back(continent);
}

int Map::getNumOfCountries()
{
	return *numOfCountries;
}

std::vector<Continent*>* Map::getContinents() {
	return continents;
}

void Map::checkConnectedGraph()
{
	std::list<Country*> BFSqueue;
	int numVisited = 0;

	//Start BFS algorithm by visiting a random country
	Country* rootCountry = continents->at(0)->getCountries()->at(0);
	BFSqueue.push_back(rootCountry);
	numVisited++;

	while (!BFSqueue.empty())
	{
		// Dequeue a vertex from BFSqueue and print it 
		rootCountry = BFSqueue.front();
		rootCountry->setVisited(true);
		BFSqueue.pop_front();
		std::cout << rootCountry->getName() << " was popped of the BFSqueue" << std::endl;
		
		//Visit all unvisited neighbouring countries and add them to the BFSqueue
		for (auto neighbour : rootCountry->getNeighbours())
		{
			if (!neighbour->getVisited())
			{
				neighbour->setVisited(true);
				numVisited++;
				BFSqueue.push_back(neighbour);
			}
		}
	}

	if (numVisited < *numOfCountries)
		std::cout << "Invalid Map. The map is not a connected graph." << std::endl << std::endl;
	else
		std::cout << "Valid Map. The map is a connected graph." << std::endl << std::endl;

	resetVisitedCountries();
}

void Map::checkConnectedSubgraph()
{
	std::list<Country*> BFSqueue;
	int numVisited = 0;
	Country* rootCountry;

	for (auto continent : *continents) {
		std::cout << "Checking the connected graph of the following continent -> " << continent->getName() << std::endl;
		numVisited = 0;
		BFSqueue.push_back(continent->getCountries()->at(0));
		numVisited++;
		while (!BFSqueue.empty())
		{
			// Dequeue a vertex from BFSqueue and print it 
			rootCountry = BFSqueue.front();
			rootCountry->setVisited(true);
			BFSqueue.pop_front();
			std::cout << rootCountry->getName() << " was popped of the BFSqueue" << std::endl;

			//Visit all unvisited neighbouring countries and add them to the BFSqueue
			for (auto neighbour : rootCountry->getNeighbours())
			{
				if (!neighbour->getVisited() && (neighbour->getContinentID() == continent->getID()))
				{
					neighbour->setVisited(true);
					numVisited++;
					BFSqueue.push_back(neighbour);
				}
			}
		}

		if (numVisited < continent->getCountries()->size())
			std::cout << "Subraph for continent " << continent->getName() << " is not a connected graph :(" << std::endl << std::endl;
		else
			std::cout << "Subraph for continent " << continent->getName() << " is a connected graph!" << std::endl << std::endl;
	}
	
	resetVisitedCountries();
}

void Map::resetVisitedCountries() {
	for (int i = 0; i < continents->size(); i++) {
		std::vector<Country*> countryList = *continents->at(i)->getCountries();
		for (int j = 0; j < countryList.size(); j++) {
			countryList.at(j)->setVisited(false);
		}
	}
}