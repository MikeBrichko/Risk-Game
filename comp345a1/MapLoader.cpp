#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Map :: Map(int numCountries){
    this->numCountries = numCountries;
    cout << "there are " << numCountries << " on this map" <<endl;
}
Country :: Country(){
        countryNum = 0;
        countryName = "noname";
        continentNum = 0;
        xC = 0;
        yC = 0;
    }
Country :: Country(int countryNum, string countryName, int continentNum, int xC, int yC){
    this->countryNum = countryNum;
    this->countryName = countryName;
    this->continentNum = continentNum;
    this->xC = xC;
    this->yC = yC;
}

Continent :: Continent(){
    continentName = "noname";
    armyValue = 0;
    color = "noColor";
}
Continent :: Continent(string continentName, int armyValue, string color ){
    this-> continentName = continentName;
    this-> armyValue = armyValue;
    this->color = color;
}

Border :: Border(){
    initCountry = 0;
    neighbourCountry = 0;
}
Border :: Border(int initCountry, int neighbourCountry){
    this->initCountry = initCountry;
    this->neighbourCountry = neighbourCountry;
}

string line, fileName;                  //strings that will iterate through file
string guideWord;                       //used to separate sections in splitString()
bool continentFound = false;            //at the end of validation, if one is false, invalid file
bool countryFound = false;
bool bordersFound = false;
bool valid = true;                  
vector<Continent> listOfContinents;     //store continents
vector<Country> listOfCountries;
vector<Border> listOfBorders;        
vector<string> words;                   //store words on each line of file
int numContinent = 0;                   
int numCountry = 0;
int numBorders = 0;


void validateMap(string s){
    cout << "validating file......" << endl;
    ifstream infile(s);
    
    while(getline(infile, line)!= NULL){  
        
    if( line.find("[continents]") == 0){
        getline(infile, line); 
        guideWord = "continent";
        while(line.find("[countries]") != 0){
            splitStringValidate(line);
            getline(infile, line);
        }
  
    }
       
    if( line.find("[countries]") == 0){
        getline(infile, line);
        guideWord = "country";
        while(line.find("[borders]") != 0){
            splitStringValidate(line);
            getline(infile, line);
            }
         }
         
         //procedure for borders
    if( line.find("[borders]") == 0){
        getline(infile, line);
        guideWord = "border";
        while(!line.empty()){
            splitStringValidate(line);
            getline(infile, line);
            } 
        }         
    }
    
    if((continentFound && countryFound && bordersFound && valid) == false){
        cout << "invalid file. Program will terminate." <<endl;
        exit(0);
    }  
      
    cout << "end of file has been reached, validation SUCCESSFULL \n\n" << endl;

    infile.close(); 
 
}
void splitStringValidate(string s){
    string element;            
    stringstream ss(s);       // Insert the string into a stream
    
    while (ss >> element){    //figure out how many words there are in the string
        words.push_back(element);
    }
    
    if(guideWord == "continent"){       //when continent is reached in file
        continentFound = true;
        if(!(words.size() == 3 || words.size() == 0)){
            valid = false;
        }
    } 
    if(guideWord == "country"){      //when country is reached in file
        countryFound = true;
        if(!(words.size() == 5 || words.size() == 0)){
            valid = false;
        }
    }
    if(guideWord == "border"){      //when continent is reached in file
        bordersFound = true;
        if(words.size() < 2){
            valid = false;
        }
    }
      
    words.clear();
}
//from .map file to an actual map object
void exportToMap(string s){
    //valid
    
    ifstream infile(s);
    
    
    while(getline(infile, line)!= NULL){  
         
         //procedure for continents
         if( line.find("[continents]") == 0){           //when found
             getline(infile, line);                     //go to next line
             cout<<"[CONTINENTS]" <<endl; 
             guideWord = "continent";
             while(line.find("[countries]") != 0){      //as long as country is not found
                splitString(line);
                numContinent++;
                getline(infile, line);
             }
  
         }
         
         //procedure for countries
         if( line.find("[countries]") == 0){
             getline(infile, line);
             cout<<"[COUNTRIES]  "<<endl;
             guideWord = "country";
             while(line.find("[borders]") != 0){
                splitString(line);
                numCountry++;
                getline(infile, line);
             }
             
         }
         
         
         //procedure for borders
         if( line.find("[borders]") == 0){
             getline(infile, line);
             cout<<"[BORDER]"<<endl;
             guideWord = "border";
             while(!line.empty()){
                splitString(line);
                getline(infile, line);
             } 
         }         
         
     } 
    cout << "end of file has been reached" << endl;
 
    infile.close(); 
}


//function to split string into individual elements
void splitString(string s){

    string element;                 
    stringstream ss(s);       // Insert the string into a stream
     
    while (ss >> element){
        words.push_back(element);
    }
    
    listOfContinents.push_back(Continent());  //initialize the vector
    listOfCountries.push_back(Country());
    
    if(guideWord == "continent"){
        listOfContinents[numContinent].continentName = words[0];        //store values of parameters
        listOfContinents[numContinent].armyValue = stoi(words[1]);
        listOfContinents[numContinent].color = words[2];
        
        cout <<"continent " << (numContinent+1) << endl;
        cout << listOfContinents[numContinent].continentName << endl;
        cout << listOfContinents[numContinent].armyValue << endl;
        cout << listOfContinents[numContinent].color <<"\n" << endl;
        
    }
    if(guideWord == "country"){
        listOfCountries[numCountry].countryNum = stoi(words[0]);
        listOfCountries[numCountry].countryName = words[1];
        listOfCountries[numCountry].continentNum =stoi(words[2]);
        listOfCountries[numCountry].xC = stoi(words[3]);
        listOfCountries[numCountry].yC = stoi(words[4]);
        
        cout <<"country " << (numCountry +1) << endl;
        cout<< listOfCountries[numCountry].countryNum <<endl;
        cout<< listOfCountries[numCountry].countryName <<endl;
        cout<< listOfCountries[numCountry].continentNum <<endl;
        cout<< listOfCountries[numCountry].xC <<endl;
        cout<< listOfCountries[numCountry].yC <<"\n"<<endl;
        
    }
    if(guideWord == "border"){
        for(int i = 1; i < words.size();i++){
            listOfBorders.push_back(Border(stoi(words[0]), stoi(words[i])));
            cout<< words[0] << " can attack " << words[i] <<endl;
        }
    }
    words.clear();
}
