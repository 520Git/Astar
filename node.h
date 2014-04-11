/*
 * node.h
 *
 *  Created on: Apr 10, 2014
 *      Author: andrew
 */

#ifndef NODE_H_
#define NODE_H_

int add(int x, int y);

class map_node {
	int xPos;
	int yPos;
	int gScore;
	int fScore;
	bool isObstructed;
	bool isClosed=0;
	//mapNode* neighbors;
public:
	void init(int xPos, int yPos, bool isClosed);
	void calculateGScore(map_node start); //Not yet implemented
	void calculateFScore(map_node start, int (*Hueristic)(map_node)); //Not yet implemented
};

map_node* initMap(int rows, int cols);




//Previously I tried using a struct (as can be seen below), I abandoned it after not being
//able to find a sensible way to initialize a 2-D array of structs. Using a class instead
//of a struct has additional advantages. For example: if I want to solve a graph where each
//node has an arbitrary and different number of neighbors keeping them in a 2D array would not
//be appropriate. As such it will be nice to have a class with functions rather than
//a struct with a bunch of functions declared separately. Still I dont know if this was the right
//choice.

//struct map_node {
//	int xPos;
//	int yPos;
//	int gScore;
//	int fScore;
//	bool isClosed=0;
//	map_node* neighbors;
//};

#endif /* NODE_H_ */
