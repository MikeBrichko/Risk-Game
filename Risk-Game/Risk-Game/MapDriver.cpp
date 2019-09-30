
#include "Map.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>


using namespace std;

// Driver program to test methods of graph class 
int main()
{

		// Create a graph and specify the number of countries it contains
		Graph g(4);

		//Create the individual countries
		Country c0(0, "Canada", "North America", 1, 1);
		Country c1(1, "USA", "North America", 1, 2);
		Country c2(2, "Mexico", "NorthAmerica", 2, 1);
		Country c3(3, "England", "Europe", 3, 2);

		//Add neighbours for each country
		g.addNeighbour(c0.countryNum, c1.countryNum);
		g.addNeighbour(c0.countryNum, c2.countryNum);
		g.addNeighbour(c1.countryNum, c2.countryNum);
		g.addNeighbour(c2.countryNum, c0.countryNum);
		g.addNeighbour(c2.countryNum, c3.countryNum);
		g.addNeighbour(c3.countryNum, c3.countryNum);


		cout << "Number of countries used: "; g.displayNumOfCountries();  //Display total number of countries

		cout << "\nShowing path of Breadth First Search Algorithm \n" << endl;

		g.BFS(0);       //Show traversal of all connected countries, specifying which country to start with

		cout << "\n\nTotal countries visited in search = "; g.displayNumVisited();   //Display total number of countries able to visit

		g.checkConnectedGraph();       //Checks if graph is a connected graph and displays message

		system("pause");

		return 0;
		
}
