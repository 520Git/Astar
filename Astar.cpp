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

map_node* map;
openQueue open_nodes;
	//This priority queue holds pointers to nodes that are open, which means
	//they are alternate paths that will be explored lowest f score first

int main() {
	//Make a random seed so that obstruction generation is different every time.
	int seed = time(0);
	srand(seed);
	//Initialize Map
	map = initMap(NUMROWS,NUMCOLS);
	//Make pointer to goal and set state appropriately
	map_node* pGoal = &map[xyc((NUMCOLS-1),(NUMROWS-1))];
	(*pGoal).state = 'G';
	//Make pointer to start, initialize state and scores appropriately, add to open_nodes queue
	map_node* pStart = &map[xyc(0,0)];
	(*pStart).state = 'S';
	pStart->gScore =0;
	pStart->fScore = pStart->gScore + pStart->xyDiffHeur(pGoal);
	pStart->isOpen =1;
	open_nodes.push(pStart); //Only the start node is in the open_nodes queue at the start
	//Add random obstructions in empty spaces
	randomizeTerrain(NUMROWS, NUMCOLS, map, 0);
	map_node* current;
	int tent_gScore;
	while(!open_nodes.empty()){
		//Print the map and wait for user to hit enter
		printMap(NUMROWS, NUMCOLS, map);
		cout << endl;
		//wait();
		//Read the lowest fScore node off the top of the queue, then pop it off
		current=open_nodes.top();
		current->isOpen=0;
		current->isClosed=1;
		open_nodes.pop();
		//Finish if the current node is the goal
		if(current->state == 'G'){
			//Retrace the shortest path by traveling backwards using cameFrom pointers
			map_node* retrace = pGoal;
			while(retrace->cameFrom->state != 'S'){
				retrace = retrace->cameFrom;
				retrace->state = 'P';
				printMap(NUMROWS, NUMCOLS, map);
				cout << endl;
				//wait();
			}
			cout << "shortest path found! This map generated with seed: " << seed << endl;
			return 1;
		}
		//Iterate through all neighbors
		for(uint i=0; i<(sizeof(current->neighbors)/sizeof(current->neighbors[1]));i++){
			map_node* neighbor = current->neighbors[i];
			if(neighbor==0) continue; //skip null neighbors
			if(neighbor->isClosed) continue; //skip closed neighbors
			if(neighbor->state == 'O') continue; //skip obstructed neighbors
			//If the neighbor is not in the closed set calculate tentative gScore;
			tent_gScore = current->gScore + 1; //This assumes the cost to move between neighbors is always 1
			if(!(neighbor->isOpen) || (tent_gScore < neighbor->gScore)){
			//If the neighbor is not in the open set, or the tentative gScore is less than the neighbors gScore
				neighbor->cameFrom = current; //Make a linked list to retrace optimal path upon completion
				neighbor->gScore = tent_gScore; //Set gScore to tentative gScore value
				neighbor->fScore = neighbor->gScore + neighbor->xyDiffHeur(pGoal); //Set fScore based on new gScore and hueristic
				forceResort(open_nodes); //Resort just in case neighbor was already in the queue and the new lower fScore would put it on top
				if(!neighbor->isOpen){ //If the neighbor is not already in the open_node queue add it
					neighbor->isOpen =1;
					open_nodes.push(neighbor);
				}
			}
		}
	}
	//If the program exits the while loop, there was no path to the goal
	cout << "Failure!: There is no path to the exit. This map generated with seed: " << seed << endl;
	return 0;
}

