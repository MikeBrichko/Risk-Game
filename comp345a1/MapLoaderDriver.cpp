#include <iostream>
#include <fstream>
#include <string>
#include "MapLoader.h"

using namespace std;


int main()
{
    string fileName;

    cout << "please enter a .map file" << endl;
    cin >> fileName;
    exportToMap(fileName);
    return 0;
}


