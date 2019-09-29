#pragma once
#include <iostream>
#include <string>
#include "Map.h"

using namespace std;
class CountryNode
{
	
public:

	string countryName1;
	string continent1;
	int player1;
	int armies;
	string borderCountries;
	string newNae;

	CountryNode(string countryName, string continent, int playerNum, int numArmies, string  neighbourCountries) {
		countryName1 = countryName;
		continent1 = continent;
		player1 = playerNum;
		armies = numArmies;
		newNae = neighbourCountries;
		
		//for (int i = 0; i < neighbourCountries.length; i++) {
		//	borderCountries[i] = neighbourCountries[i];
		//}
	}
};



