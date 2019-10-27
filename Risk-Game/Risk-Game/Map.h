#pragma once
#include <string>
#include <iostream>
#include <vector>

class Country {
private:
	int* ID;
	std::string* name;
	int* continentID;
	int* playerID;
	int* armies;
	bool* visited;
	std::vector<Country*>* neighbours;

public:
	Country(int countryID, std::string countryName, int countryContinentID, int countryArmies);
	~Country();
	void addNeighbour(Country* country);
	int getID();
	std::string getName();
	std::vector<Country*> getNeighbours();
	int getContinentID();
	bool getVisited();
	void setVisited(bool countryVisited);
	void setArmies(int armies); // used in reinforce 
	int getArmies();
};

class Continent {
private:
	int* ID;
	std::string* name;
	int* armyValue;
	std::vector<Country*>* countries;

public:
	Continent(int continentID, std::string continentName, int continentArmyValue);
	~Continent();
	void addCountry(Country* country);
	std::vector<Country*>* getCountries();
	std::string getName();
	int getID();
};

class Map {
private:
	int* numOfCountries;                
	std::vector<Continent*>* continents;  

public:
	Map(int numOfCountries);
	~Map();
	void addContinent(Continent* continent);
	int getNumOfCountries();
	void checkConnectedGraph();
	void checkConnectedSubgraph();
	void resetVisitedCountries();
};