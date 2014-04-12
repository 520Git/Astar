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
using namespace std;





map_node* map;
std::priority_queue<map_node*> open_nodes;
					//This priority queue holds pointers to nodes that are open, which means
					//they are alternate paths that will be explored lowest f score first

int main() {

	map = initMap(NUMROWS,NUMCOLS);
	debugNeighbors(map);

	return 0;
}

