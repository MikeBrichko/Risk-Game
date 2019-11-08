#include "MapLoader.h"'
#include <iostream>
#include <string>

/**int main()
{
	
	//Case 1: Valid map
	
	MapLoader* mapLoader = new MapLoader("eupe.map");
    mapLoader->validateMap();
	Map* map = mapLoader->exportToMap();
	map->checkConnectedGraph();
	map->checkConnectedSubgraph();
	
	std :: cout <<"--------------------------------------" << std :: endl;

	//Case 2: Invalid map
	
	MapLoader* mapLoaderFail = new MapLoader("europe_fail.map");
	mapLoaderFail->validateMap();

    return 0;
}**/



