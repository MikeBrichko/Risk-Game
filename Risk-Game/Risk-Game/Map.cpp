#pragma once
#include "Map.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>


using namespace std;

list<int>* neighbours;   //pointer to list 

//Constructor for graph object
Graph::Graph(int numOfCountries)
{
	this->numOfCountries = numOfCountries;
	neighbours = new list<int>[numOfCountries];      //create an array of lists, save pointer in neighbours
}                                                    

//Constructor for Country object
Country::Country(int countryNum, std::string countryName, std::string continent, int playerNum, int armies)
{
	this->countryNum = countryNum;
	this->countryName = countryName;
	this->continent = continent; 
	this->playerNum = playerNum;
	this->armies = armies;
}

//Constructor for continent object
Continent::Continent(int continentNum, string continentName, std::vector<Country> listOfCountries) {
	this->continentNum = continentNum;
	this->continentName = continentName;
	this->listOfCountries = listOfCountries;
}

//Function to add a neighbouring country 
void Graph::addNeighbour(int country, int neighbour)
{
	neighbours[country].push_back(neighbour); // Add neighbour to country’s list. 
	neighbours[neighbour].push_back(country); // Also arrow to backwards
}

//Function to display number of Countries
void Graph::displayNumOfCountries()
{
	cout << numOfCountries << endl;
}


//Function to check if the map is a connected graph
//This is a Breadth First Search Algoirthm (takes the first country number as parameter)
void Graph::checkConnectedGraph(int s)
{
	int numVisited = 1;
	// Mark all the vertices as not visited 
	bool* visited = new bool[numOfCountries]; //Create array of booleans for the countries visited
	for (int i = 0; i < numOfCountries; i++)  //Initialize all to false (all countries have not been visited yet)
		visited[i] = false;
	list<int> queue;  //Create a queue needed for the BFS algorithm
	visited[s] = true;    //Mark first country node as visited
	queue.push_back(s);   //Add the first country to the queue
	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<int>::iterator i;
	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.front();
		//cout << s << " ";
		queue.pop_front();
		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (i = neighbours[s].begin(); i != neighbours[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				numVisited++;
				queue.push_back(*i);
			}
		}
	}
	if (numVisited < numOfCountries)
		cout << "\nInvalid Map. The map is not a connected graph.\n" << endl;
	else
		cout << "\nValid Map. The map is a connected graph.\n" << endl;
}


//Function to check if continents are a connected subgraph 
//This is a Breadth First Search Algorithm (takes the first country number and continent object as parameters)

bool Graph::checkConnectedSubgraph(int s, Continent cont)
{
	int numVisited = 1;
	int numOfCountriesInContinent = cont.listOfCountries.size();

	// Mark all the vertices as not visited 
	bool* visited = new bool[numOfCountries]; //Create array of booleans for the countries visited
	for (int i = 0; i < numOfCountries; i++)  //Initialize all to false (all countries have not been visited yet)
		visited[i] = false;

	int* specificNum = new int[numOfCountriesInContinent];
	bool* continentCheck = new bool(false);
	for (int i = 0; i < numOfCountriesInContinent; i++) {
		specificNum[i] = cont.listOfCountries.at(i).countryNum;
		if (specificNum[i] == s)
			*continentCheck = true;
	}
	if (!*continentCheck) {
		cout << "Current node does not exist in given Continent";
		return false;
	}
	list<int> queue;  //Create a queue needed for the BFS algorithm

	visited[s] = true;    //Mark first country node as visited
	queue.push_back(s);   //Add the first country to the queue

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<int>::iterator i;

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.front();
		//cout << s << " ";
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (i = neighbours[s].begin(); i != neighbours[s].end(); ++i)
		{
			for (int j = 0; j < numOfCountriesInContinent; j++) {
				if (specificNum[j] == *i) {
					if (!visited[*i])
					{
						visited[*i] = true;
						numVisited++;
						queue.push_back(*i);

					}
				}
			}
		}
	}

	for (int i = 0; i < numOfCountriesInContinent; i++) {
		if (!visited[specificNum[i]]) {
			cout << "Invalid continent. The continent is not a connected subgraph.\n" << endl;
			return false;
		}
	}
	cout << "Valid continent. The continent is a connected subgraph.\n" << endl;
	return true;
}


