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
            cout << word <<endl;
            word = "";
        }
        else{
            word = word + x;
        }
    }
    cout<< word <<endl;
}
//validate() function
void validateMap(string s){
    bool valid;
    
    
}

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

