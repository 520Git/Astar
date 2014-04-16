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
	int seed = time(0); //hard seed:1397595742 8x8 .25
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
	randomizeTerrain(NUMROWS, NUMCOLS, map, 0.45);

	//Debugging code
	cout<< "The true map" <<endl;
	printMap(NUMROWS,NUMCOLS,map,0);
	cout<< endl;

	//Run Astarr
	if(repAStar(NUMROWS,NUMCOLS,map,pStart,pGoal)){
		printMap(NUMROWS, NUMCOLS, map,0);
		cout << "Success:Shortest path found! Terrain generated with seed:" << seed << endl;
	}else{
		printMap(NUMROWS, NUMCOLS, map,0);
		cout << "Failure: No path to goal! Terrain generated with seed:" << seed << endl;
	}
	return 0;
}

