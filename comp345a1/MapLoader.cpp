#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Map.h"
#include "MapLoader.h"

using namespace std;

string line, fileName;
vector<string> words; 

//from .map file to an actual map object
void exportToMap(string s){
    //valid
    
    ifstream infile(s);
    
    while(getline(infile, line)!= NULL){  
         
         //procedure for continents
         if( line.find("[continents]") == 0){
             getline(infile, line); //go to next line
             cout<<"[CONTINENTS] DETECTED" <<endl;            
             while(line.find("[countries]") != 0){
                splitString(line);
                getline(infile, line);
             }
  
         }
         
         //procedure for countries
         if( line.find("[countries]") == 0){
             getline(infile, line);
             cout<<"[countries] DETECTED "<<endl;
             while(line.find("[borders]") != 0){
                splitString(line);
                getline(infile, line);
             }
         }
         
         //procedure for borders
         if( line.find("[borders]") == 0){
             getline(infile, line);
             cout<<"[borders] DETECTED"<<endl;
             while(!line.empty()){
                splitString(line);
                getline(infile, line);
             } 
         }         
         cout << line <<"\n";
     } 
    cout << "end of file has been reached" << endl;
 
    infile.close(); 
}
//function to split string into individual elements
void splitString(string s){

    string buf;                 // Have a buffer string
    stringstream ss(s);       // Insert the string into a stream

    while (ss >> buf){
        words.push_back(buf);
    }
    for(int i = 0; i < words.size(); i++){
        cout<<words[i]<<endl;
    }
}