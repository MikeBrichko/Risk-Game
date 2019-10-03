#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string line;
string fileName;

//function to split string into individual elements
void splitString(string s){
    string word = "";
    for (auto x : s) {
        if(x == ' '){
            cout << word << " has been stored"<<endl;
            word = "";
        }
        else{
            word = word + x;
            
        }
    }
    cout<< word<<endl;
    cout<<"has been stored \n"<<endl;
}
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


int main()
{
    cout << "please enter a .map file" << endl;
    cin >> fileName;
    exportToMap(fileName);
    return 0;
}

