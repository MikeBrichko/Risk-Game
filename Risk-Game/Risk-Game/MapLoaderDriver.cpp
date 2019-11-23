#include "MapLoader.h"
#include <iostream>
#include <string>

/**int main()
{
	
	//Case 1: Valid map
	
	DominationMapLoader* mapLoader = new DominationMapLoader("eupe.map");
    mapLoader->dominationValidateMap();
	Map* map = mapLoader->dominationExportToMap();
	map->checkConnectedGraph();
	map->checkConnectedSubgraph();
	
	std :: cout <<"--------------------------------------" << std :: endl;

	//Case 2: Invalid map
	
	DominationMapLoader* mapLoaderFail = new DominationMapLoader("europe_fail.map");
	mapLoaderFail->dominationValidateMap();

    return 0;
}**/



