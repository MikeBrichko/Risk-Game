#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Map{
public: 
    int numCountries;
    Map(int numCountries);
};

class Country{
public:
    int countryNum;
    string countryName;
    int continentNum;               
    int xC;                          //xCoordinate
    int yC;                          //yCoordinate
    
    Country();
    Country(int countryNum, string countryName, int continentNum, int xC, int yC);
};

class Continent{
public :
    string continentName;
    int armyValue;
    string color;
    
    Continent();
    Continent(string continentName, int armyValue, string color );
};

class Border{
public:
    int initCountry;
    int neighbourCountry;
    
    Border();
    Border(int initCountry, int neighbourCountry);
};

void splitString(string s);
void exportToMap(string s);
void validateMap(string s);
void splitStringValidate(string s);
void countWords(string s);

    
    
