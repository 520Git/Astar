/*
 * node.h
 *
 *  Created on: Apr 10, 2014
 *      Author: andrew
 */

#ifndef NODE_H_
#define NODE_H_

#define NUMROWS 40
#define NUMCOLS 40 //Make sure to change the companion #define in the next file
#define NUMNEIGHBS 4

#define ijc(i,j) (i*NUMCOLS+j)
#define xyc(x,y) (y*NUMCOLS+x)

#include <queue>
using namespace std;

class map_node {
private:
public:
	int xPos, yPos;
	float gScore,fScore;
	char state;
	// O = obstructed
	// S = start
	// G = goal
	//" "= unobstructed;
	bool isClosed=0;
	bool isOpen=0;
	map_node* neighbors[NUMNEIGHBS];
	map_node* cameFrom;
	void init(int xPos, int yPos, bool isClosed);
	void calculateFScore(map_node goal, float (*Hueristic)(map_node)); //Not yet implemented
	void initNeighbors(int rows, int cols, map_node* map);
	float xyDiffHeur(map_node* pGoal);
};

//Class that defines the > operator for map_node so that priority_queue can sort them
//Note: the default is that priority queue sorts greatest at the top, with the default
//operator being < . We want least at the top so we make this operator implement > .
class compareNode {
private:
public:
	bool operator()(map_node* n1, map_node* n2){
		if(n1->fScore  > n2->fScore) return true;
		else return false;
	}
};

typedef std::priority_queue<map_node*,vector<map_node*>,compareNode> openQueue;

map_node* initMap(int rows, int cols);
void randomizeTerrain(int rows, int cols, map_node* map, float pObs);
void debugNeighbors(map_node* map);
void printMap(int rows, int cols, map_node* map);
void wait();
void forceResort(openQueue open_nodes);

#endif /* NODE_H_ */
