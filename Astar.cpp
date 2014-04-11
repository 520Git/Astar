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

//Initialize dimension of map and data structures for algorithm
const int n=60;
const int m=80;
map_node* map;  	//This stores information on if a node is obstructed or not, on the
					//closed list or not as well as its g and f scores. It stores xpos and
					//ypos as well but that may be redundant because the order of the elements
					//in the array also implicitly store that information. I have also been arguing
					//with myself as to whether storing isClosed in this way is a good idea. (the
					//other option is to keep a separate list). I believe isClosed should be a
					//property of the nodes because it is much easier to check if your neighbor has
					//a certain property than if your neighbor is a member of some huge list
std::priority_queue<map_node*> open_nodes;
					//This priority queue holds pointers to nodes that are open, which means
					//they are alternate paths that will be explored lowest f score first

map_node test;

int main() {
	test.init(0,0,0);
	map=initMap(n,m); //Is this actually going to work? Or am I pointing to something that will cease to exist?
	//In any case I am not very happy with this because I will have to macro "i*cols+j" to treat this like a 2d array


	//cout << "!!!Hello World!!! ?" << endl; // prints !!!Hello World!!! ?
	return 0;
}
