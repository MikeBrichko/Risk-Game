#include "Map.h"
#include <iostream>
#include <string>
#include <list>

/**int main()
{
	//Use Case 1
	//A---B
	//|	  |
	//C---D , where A&B belong to Continent1 and C&D belong to Continent2
	
	std::cout << "Use case 1" << std::endl;
	Map* map = new Map(4);

	Continent* Continent1 = new Continent(1, "continent1", 5);
	Continent* Continent2 = new Continent(2, "continent2", 5);
	map->addContinent(Continent1);
	map->addContinent(Continent2);

	Country* A = new Country(1, "A", Continent1->getID(), 0);
	Country* B = new Country(2, "B", Continent1->getID(), 0);
	Country* C = new Country(3, "C", Continent2->getID(), 0);
	Country* D = new Country(4, "D", Continent2->getID(), 0);
	Continent1->addCountry(A);
	Continent1->addCountry(B);
	Continent2->addCountry(C);
	Continent2->addCountry(D);
	
	A->addNeighbour(B);
	A->addNeighbour(C);
	B->addNeighbour(A);
	B->addNeighbour(D);
	C->addNeighbour(A);
	C->addNeighbour(D);
	D->addNeighbour(B);
	D->addNeighbour(C);

	map->checkConnectedGraph();
	map->checkConnectedSubgraph();

	//Use Case 2
	//E   F
	//|	  |
	//G---H , where E&F belong to Continent3 and G&H belong to Continent4
	
	std::cout << "Use case 2" << std::endl;
	Map* map1 = new Map(4);

	Continent* Continent3 = new Continent(3, "continent3", 5);
	Continent* Continent4 = new Continent(4, "continent4", 5);
	map1->addContinent(Continent3);
	map1->addContinent(Continent4);

	Country* E = new Country(5, "E", Continent3->getID(), 0);
	Country* F = new Country(6, "F", Continent3->getID(), 0);
	Country* G = new Country(7, "G", Continent4->getID(), 0);
	Country* H = new Country(8, "H", Continent4->getID(), 0);
	Continent3->addCountry(E);
	Continent3->addCountry(F);
	Continent4->addCountry(G);
	Continent4->addCountry(H);

	E->addNeighbour(G);
	F->addNeighbour(H);
	G->addNeighbour(E);
	G->addNeighbour(H);
	H->addNeighbour(F);
	H->addNeighbour(G);

	map1->checkConnectedGraph();
	map1->checkConnectedSubgraph();

	
	//Use Case 3
	//I   J	
	//
	//K---L , where I&J belong to Continent5 and K&L belong to Continent6
	
	std::cout << "Use case 3" << std::endl;
	Map* map2 = new Map(4);

	Continent* Continent5 = new Continent(5, "continent5", 5);
	Continent* Continent6 = new Continent(6, "continent6", 5);
	map2->addContinent(Continent5);
	map2->addContinent(Continent6);

	Country* I = new Country(9, "I", Continent5->getID(), 0);
	Country* J = new Country(10, "J", Continent5->getID(), 0);
	Country* K = new Country(11, "K", Continent6->getID(), 0);
	Country* L = new Country(12, "L", Continent6->getID(), 0);
	Continent5->addCountry(I);
	Continent5->addCountry(J);
	Continent6->addCountry(K);
	Continent6->addCountry(L);

	K->addNeighbour(L);
	L->addNeighbour(K);

	map2->checkConnectedGraph();
	map2->checkConnectedSubgraph();
	
	return 0;
}**/
