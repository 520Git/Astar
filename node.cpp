/*
 * node.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: andrew
 */
#include "node.h"
#include <cstring>


//Test function to check my ability to change the values of a map_node
void map_node::init(int x, int y, bool z){
	xPos=x;
	yPos=y;
	isClosed = z;
	return;
};


//Function to test my ability to initialize an array of nodes.
//In the future this would initialize some of them randomly
//as obstructed
map_node* initMap(int rows, int cols){
	size_t s = sizeof(map_node)*rows*cols;
	map_node* map = new map_node[s];
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			map[i*cols+j].init(0,0,0);
		}
	}
	return map;
}

