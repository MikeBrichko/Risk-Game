#include "MapLoader.h"'
#include <iostream>
#include <string>

int main()
{
	MapLoader* mapLoader = new MapLoader("europe.map");
    mapLoader->validateMap();
	Map* map = mapLoader->exportToMap();
	map->checkConnectedGraph();
	map->checkConnectedSubgraph();

	MapLoader* mapLoaderFail = new MapLoader("europe_fail.map");
	mapLoaderFail->validateMap();
	Map* map2 = mapLoaderFail->exportToMap();

    return 0;
}



