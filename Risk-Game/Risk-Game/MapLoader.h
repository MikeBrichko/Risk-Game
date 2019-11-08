#pragma once
#include <string>
#include "Map.h"

class MapLoader {
private: 
	std::string* fileName;
	bool validateContinents(std::string lineToValidate);
	bool validateCountries(std::string lineToValidate);
	bool validateBorders(std::string lineToValidate);
	Continent* createContinent(std::string line, int continentID);
	Country* createCountry(std::string line, std::vector<Continent*>* continents);
	void createBorders(std::string line, std::vector<Country*>* countries);

public:
	MapLoader(std::string fileName);
	~MapLoader();
	bool validateMap();
	Map* exportToMap();
};


    
    
