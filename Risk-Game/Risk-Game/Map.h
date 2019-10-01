
#pragma once
#include <string>
using namespace std;



class Graph {

	int numOfCountries;                   //Total number of Countries 

	int numVisited = 1;					  //Number of countries visited by BFS algorithm

public:

	Graph(int numOfCountries);

	void addNeighbour(int v, int w);	//function to add neighbour country to a country

	void BFS(int start);				//function that first country number as parameter and perform BFS algorithm

	void checkConnectedGraph();			//function that checks if the map is a connected graph

	void displayNumOfCountries();		//function that displays total number of countries

	void displayNumVisited();			//function that displays total number of unique countries visited by BFS algorithm
};

class Country {

public:

	int countryNum;             //Number identifier corresponding to a country

	string countryName;			//Name of the country

	string continent;			//Name of the continent the country belongs to

	int playerNum;				//The player controlling the current country (ex: player 1, 2, 3, or 4 etc...)

	int armies;					//The number of armies places on the country at the moment

	//Constructors

	Country(int countryNum);

	Country(int countryNum, string countryName, string continent, int playerNum, int armies);

};

