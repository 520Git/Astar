/*
 * node.h
 *
 *  Created on: Apr 10, 2014
 *      Author: andrew
 */

#ifndef NODE_H_
#define NODE_H_

#define NUMROWS 16
#define NUMCOLS 140 //Make sure to change the companion #define in the next file

#define ijc(i,j) (i*NUMCOLS+j)
#define xyc(x,y) (y*NUMCOLS+x)

int add(int x, int y);

class map_node {

public:
	int xPos, yPos,gScore,fScore;
	char state;
	// O = obstructed
	// S = start
	// G = goal
	//" "= unobstructed;
	bool isClosed=0;
	map_node* neighbors[4];
	void init(int xPos, int yPos, bool isClosed);
	void calculateGScore(map_node start); //Not yet implemented
	void calculateFScore(map_node start, int (*Hueristic)(map_node)); //Not yet implemented
	void initNeighbors(int rows, int cols, map_node* map);
};

map_node* initMap(int rows, int cols);
void randomizeTerrain(int rows, int cols, map_node* map, float pObs);
void debugNeighbors(map_node* map);
void printMap(int rows, int cols, map_node* map);

#endif /* NODE_H_ */
