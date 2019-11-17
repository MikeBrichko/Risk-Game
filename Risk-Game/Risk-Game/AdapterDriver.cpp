#include "MapLoader.h"
#include <iostream>
#include <string>

int main()
{
	ConquestMapLoader* maploaderC = new ConquestMapLoader("Alberta.map");
	maploaderC->conquestValidateMap();
	Map* conquestMap = maploaderC->conquestExportToMap();
	conquestMap->checkConnectedGraph();
	conquestMap->checkConnectedSubgraph();

	TwoWayMapAdapter* conquestAdapter = new TwoWayMapAdapter(maploaderC);
	conquestAdapter->dominationValidateMap();
	Map* validatedConquestMap = conquestAdapter->dominationExportToMap();
	validatedConquestMap->checkConnectedGraph();
	validatedConquestMap->checkConnectedSubgraph();

	//-------------------------------------------------------------------------------------------------------------

	DominationMapLoader* mapLoaderD = new DominationMapLoader("europe.map");
	mapLoaderD->dominationValidateMap();
	Map* dominationMap = mapLoaderD->dominationExportToMap();
	dominationMap->checkConnectedGraph();
	dominationMap->checkConnectedSubgraph();

	TwoWayMapAdapter* dominationAdapter = new TwoWayMapAdapter(mapLoaderD);
	dominationAdapter->conquestValidateMap();
	Map* validatedDominationMap = dominationAdapter->conquestExportToMap();
	validatedDominationMap->checkConnectedGraph();
	validatedDominationMap->checkConnectedSubgraph();

	return 0;
}