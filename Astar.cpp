//============================================================================
// Name        : Astar.cpp
// Author      : Andrew Vaziri
// Version     :
// Copyright   : none
// Description : A* Search
//============================================================================
#include <iostream>
#include "node.h"
#include <stdlib.h> //for rand
using namespace std;

map_node *map, *map2;
	//This priority queue holds pointers to nodes that are open, which means
	//they are alternate paths that will be explored lowest f score first

int main() {
	//Make a random seed so that obstruction generation is different every time.
	int seed = 1397595742; //time(0); //hard seed:1397595742 8x8 .25
	srand(seed);
	//Initialize Map
	map = initMap(NUMROWS,NUMCOLS);
	//Make pointer to goal and set state appropriately
	map_node* pGoal = &map[xyc((NUMCOLS-1),(NUMROWS-1))];
	(*pGoal).state = 'G';
	//Make pointer to start, initialize state and scores appropriately, add to open_nodes queue
	map_node* pStart = &map[xyc(0,0)];
	(*pStart).state = 'S';
	//Add random obstructions in empty spaces
	randomizeTerrain(NUMROWS, NUMCOLS, map, 0.25);
	//Deep Copy the map for further tests;
	map2=deepCopyMap(NUMROWS,NUMCOLS,map);

	//Run Astar
	if(aStar(NUMROWS,NUMCOLS,map)){
		printMap(NUMROWS, NUMCOLS, map);
		cout << "Success:Shortest path found! Terrain generated with seed:" << seed << endl;
	}else{
		printMap(NUMROWS, NUMCOLS, map);
		cout << "Failure: No path to goal! Terrain generated with seed:" << seed << endl;
	}
	return 0;
}

