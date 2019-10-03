
#pragma once
#include <string>
#include <istream>
#include <vector>
class Continent;

class Graph {

	int numOfCountries;                   //Total number of Countries 

	int numVisited = 1;					  //Number of countries visited by BFS algorithm

public:

	Graph(int numOfCountries);

	void addNeighbour(int v, int w);	//function to add neighbour country to a country

	bool BFS(int start, Continent cont);				//function that first country number as parameter and perform BFS algorithm

	void checkConnectedGraph();			//function that checks if the map is a connected graph

	void displayNumOfCountries();		//function that displays total number of countries

	void displayNumVisited();			//function that displays total number of unique countries visited by BFS algorithm
};

class Country {

public:
	int countryNum;             //Number identifier corresponding to a country

	std::string countryName;			//Name of the country

	std::string continent;			//Name of the continent the country belongs to

	int playerNum;				//The player controlling the current country (ex: player 1, 2, 3, or 4 etc...)

	int armies;					//The number of armies places on the country at the moment
	//Constructors

	//Country(int countryNum);

	Country(int countryNum, std::string countryName, std::string continent, int playerNum, int armies);
};

class Continent {
public:
	Continent(int continentNum, std::string continentName, std::vector<Country> listOfCountries);
	int continentNum;
	std::string continentName;
	std::vector<Country> listOfCountries;

private:

};
