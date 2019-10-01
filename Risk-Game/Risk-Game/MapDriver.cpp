
#include "Map.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>


using namespace std;

// Driver program to test methods of graph class 
int main()
{

		//Example of a Valid Map
		
		// Create a graph and specify the number of countries it contains
		Graph g(8);

		//Create the individual countries
		Country c0(0, "Canada", "North America", 1, 1);
		Country c1(1, "USA", "North America", 1, 2);
		Country c2(2, "Mexico", "NorthAmerica", 2, 1);
		Country c3(3, "England", "Europe", 3, 2);
		Country c4(4, "France", "Europe", 3, 1);
		Country c5(5, "Netherlands", "Europe", 1, 0);
		Country c6(6, "China", "Asia", 3, 1);
		Country c7(7, "Japan", "Asia", 1, 0);

		//Add neighbours for each country
		g.addNeighbour(c0.countryNum, c1.countryNum);
		g.addNeighbour(c0.countryNum, c2.countryNum);
		g.addNeighbour(c1.countryNum, c2.countryNum);
		g.addNeighbour(c2.countryNum, c3.countryNum);
		g.addNeighbour(c2.countryNum, c3.countryNum);
		g.addNeighbour(c3.countryNum, c4.countryNum);
		g.addNeighbour(c4.countryNum, c5.countryNum);
		g.addNeighbour(c4.countryNum, c6.countryNum);
		g.addNeighbour(c6.countryNum, c7.countryNum);

		


		cout << "Number of countries used: "; g.displayNumOfCountries();  //Display total number of countries

		cout << "\nShowing path of Breadth First Search Algorithm \n" << endl;

		g.BFS(0);       //Show traversal of all connected countries, specifying which country to start with

		cout << "\n\nTotal unique countries visited in search = "; g.displayNumVisited();   //Display total number of countries able to visit

		g.checkConnectedGraph();       //Checks if graph is a connected graph and displays message
		
		

		/*
		//Example of an Invalid Map
		
		// Create a graph and specify the number of countries it contains
		Graph g(8);

		Country c0(0, "Canada", "North America", 1, 1);
		Country c1(1, "USA", "North America", 1, 2);
		Country c2(2, "Mexico", "NorthAmerica", 2, 1);
		Country c3(3, "England", "Europe", 3, 2);
		Country c4(4, "France", "Europe", 3, 1);
		Country c5(5, "Netherlands", "Europe", 1, 0);
		Country c6(6, "China", "Asia", 3, 1);
		Country c7(7, "Japan", "Asia", 1, 0);


		//Add neighbours for each country
		g.addNeighbour(c0.countryNum, c1.countryNum);
		g.addNeighbour(c0.countryNum, c2.countryNum);
		g.addNeighbour(c1.countryNum, c2.countryNum);
		g.addNeighbour(c2.countryNum, c3.countryNum);
		g.addNeighbour(c2.countryNum, c3.countryNum);
		g.addNeighbour(c3.countryNum, c4.countryNum);
		g.addNeighbour(c4.countryNum, c5.countryNum);
		g.addNeighbour(c6.countryNum, c7.countryNum);


		cout << "Number of countries used: "; g.displayNumOfCountries();  //Display total number of countries

		cout << "\nShowing path of Breadth First Search Algorithm \n" << endl;

		g.BFS(0);       //Show traversal of all connected countries, specifying which country to start with

		cout << "\n\nTotal unique countries visited in search = "; g.displayNumVisited();   //Display total number of countries able to visit

		g.checkConnectedGraph();       //Checks if graph is a connected graph and displays message
		*/



		system("pause");

		return 0;
		
}
