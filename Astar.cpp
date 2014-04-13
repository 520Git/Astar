//============================================================================
// Name        : Astar.cpp
// Author      : Andrew Vaziri
// Version     :
// Copyright   : none
// Description : A* Search
//============================================================================
#include <iostream>
#include <queue>
#include "node.h"
#include <stdlib.h> //for rand
using namespace std;

map_node* map;
std::priority_queue<map_node*> open_nodes;
	//This priority queue holds pointers to nodes that are open, which means
	//they are alternate paths that will be explored lowest f score first

int main() {
	//Make a random seed so that obstruction generation is different every time.
	srand(time(0));
	//Initialize Map, Make Terrain
	map = initMap(NUMROWS,NUMCOLS);
	randomizeTerrain(NUMROWS, NUMCOLS, map, .15);
	//Make pointers to start and goal, and set their states appropriately;
	map_node* pStart = &map[xyc(0,0)];
	(*pStart).state = 'S';
	//open_nodes.pop()
	map_node* pGoal = &map[xyc((NUMCOLS-1),(NUMROWS-1))];
	(*pGoal).state = 'G';
	//Print the map
	printMap(NUMROWS, NUMCOLS, map);
	//Main Search loop
	while(!open_nodes.empty()){



		printMap(NUMROWS, NUMCOLS, map);
		wait();
	}
	return 0;
}

