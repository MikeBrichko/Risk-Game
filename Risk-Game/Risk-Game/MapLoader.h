#pragma once
#include <string>
#include "Map.h"

class DominationMapLoader {
private: 
	std::string* dominationFileName;
	bool validateContinents(std::string lineToValidate);
	bool validateCountries(std::string lineToValidate);
	bool validateBorders(std::string lineToValidate);
	Continent* createContinent(std::string line, int continentID);
	Country* createCountry(std::string line, std::vector<Continent*>* continents);
	void createBorders(std::string line, std::vector<Country*>* countries);

public:
	DominationMapLoader();
	DominationMapLoader(std::string dominationFileName);
	~DominationMapLoader();
	bool dominationValidateMap();
	Map* dominationExportToMap();
};

class ConquestMapLoader {
private:
	std::string* conquestFileName;
	bool conquestValidateContinents(std::string lineToValidate);
	bool checkIfNumber(std::string);
	bool conquestValidateCountries(std::string);
	bool conquestValidateBorders(std::string);
	Continent* conquestCreateContinent(std::string line, int continentID);
	Country* conquestCreateCountry(int countryID, std::string line, std::vector<Continent*>* continents);
	void conquestCreateBorders(std::string line, std::vector<Country*>* countries);

public:
	ConquestMapLoader();
	ConquestMapLoader(std::string conquestFileName);
	~ConquestMapLoader();
	bool conquestValidateMap();
	Map* conquestExportToMap();
};

class TwoWayMapAdapter : public DominationMapLoader, public ConquestMapLoader {
private:
	DominationMapLoader* dominationMapLoader;
	ConquestMapLoader* conquestMapLoader;
public:
	TwoWayMapAdapter(DominationMapLoader* newMapLoader);
	TwoWayMapAdapter(ConquestMapLoader* newConquestMapLoader);
	bool conquestValidateMap();
	Map* conquestExportToMap();
	bool dominationValidateMap();
	Map* dominationExportToMap();
};


    
    
