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

const int n=60;   //Initialize dimensions and map
const int m=80;
int map[n][m];
//int closed_nodes[n][m];
//int dir_map[n][m];
std::priority_queue<int> open_nodes;  	//Initialize a priority queue for the open nodes



int main() {
	cout << "!!!Hello World!!! ?" << endl; // prints !!!Hello World!!! ?
	cout << add(n,m) << endl;
	return 0;
}
