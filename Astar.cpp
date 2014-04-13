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
std::priority_queue<map_node*,vector<map_node*>,compareNode> open_nodes;
	//This priority queue holds pointers to nodes that are open, which means
	//they are alternate paths that will be explored lowest f score first

int main() {

	//Testing priority queue.


	map_node greatest;
	greatest.fScore = 1000;
	open_nodes.push(&greatest);
	cout << open_nodes.top()->fScore << endl;
	greatest.fScore = 999;
	cout << open_nodes.top()->fScore << endl;
	map_node mid;
	mid.fScore = 730;
	open_nodes.push(&mid);
	cout << open_nodes.top()->fScore << endl;
	map_node least;
	least.fScore = 50;
	open_nodes.push(&least);
	cout << open_nodes.top()->fScore << endl;

	//Test if the nodes re-order if I change one of the values
	least.fScore=5000;
	greatest.fScore=600;
	cout << open_nodes.top()->fScore << endl;
	cout << open_nodes.size() << endl;
	open_nodes.pop();
	cout << open_nodes.size() << endl;
	cout << open_nodes.top()->fScore << endl;
	return 0;




	//Make a random seed so that obstruction generation is different every time.
	srand(time(0));
	//Initialize Map
	map = initMap(NUMROWS,NUMCOLS);
	//Make pointers to start and goal, and set their states appropriately;
	map_node* pStart = &map[xyc(0,0)];
	(*pStart).state = 'S';
	//open_nodes.pop()
	map_node* pGoal = &map[xyc((NUMCOLS-1),(NUMROWS-1))];
	(*pGoal).state = 'G';
	//Add random obstructions in empty spaces
	randomizeTerrain(NUMROWS, NUMCOLS, map, .15);
	//Print the map
	printMap(NUMROWS, NUMCOLS, map);
	//Main Search loop
	while(!open_nodes.empty()){



		printMap(NUMROWS, NUMCOLS, map);
		wait();
	}
	return 0;
}

