#pragma once
#include "Map.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>


using namespace std;

list<int>* neighbours;            //doubly linked list called neighbours


//Constructor for graph object
Graph::Graph(int numOfCountries)
{
	this->numOfCountries = numOfCountries;
	neighbours = new list<int>[numOfCountries];
}

//Constructors for Country objects
Country::Country(int countryNum)
{
	this->countryNum = countryNum;
}

Country::Country(int countryNum, string countryName, string continent, int playerNum, int armies)
{
	this->countryNum = countryNum;
	this->countryName = countryName;
	this->continent = continent; 
	this->playerNum = playerNum;
	this->armies = armies;
}

//Function to add a neighbouring country 
void Graph::addNeighbour(int v, int w)
{
	neighbours[v].push_back(w); // Add w to v’s list. 
}

//Function to check if the Map is a connected graph
void Graph::checkConnectedGraph()
{
	if (numVisited < numOfCountries)
		cout << "\nInvalid Map. The map is not a connected graph.\n" << endl;
	else
		cout << "\nValid Map. The map is a connected graph.\n" << endl;
}

void Graph::displayNumOfCountries()
{
	cout << numOfCountries << endl;
}

void Graph::displayNumVisited()
{
	cout << numVisited << endl;
}


//Breadth First Search Algorithm to traverse all countries possible in a connected graph (takes first country number as parameter)
void Graph::BFS(int s)
{
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
		cout << s << " ";
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


}


