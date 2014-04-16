/*
 * node.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: andrew
 */
#include "node.h"
#include <cstring>
#include <iostream>
#include <limits> //Included for debug function wait
#include <math.h>
#include <stdlib.h> //for rand
using namespace std;


//Test function to check my ability to change the values of a map_node
void map_node::init(int x, int y, bool z){
	xPos=x;
	yPos=y;
	isClosed = z;
	return;
};

//Function to initialize the pointers to neighbors so I can traverse the nodes like a graph
//Rather than rely on the simple case of a 2d array
void map_node::initNeighbors(int rows, int cols, map_node* map){
	if(NUMNEIGHBS==4){
	//Give all nodes four neighbors, nodes on edges have null pointer neighbors
	if((yPos-1)==-1)neighbors[0]=0;
	else neighbors[0]=&map[xyc(xPos,(yPos-1))];    //above
	if((xPos+1)==cols)neighbors[1]=0;
	else neighbors[1]=&map[xyc((xPos+1),yPos)];    //right
	if((yPos+1)==rows) neighbors[2]=0;
	else neighbors[2]=&map[xyc(xPos,(yPos+1))];    //below
	if((xPos-1)==-1)neighbors[3]=0;
	else neighbors[3]=&map[xyc((xPos-1),yPos)];         //left
	return ;
	}else if(NUMNEIGHBS==8){
		int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
		int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
		for(uint i=0; i<NUMNEIGHBS; i++){
			if((yPos+dy[i]==-1)||(yPos+dy[i]==rows)||(xPos+dx[i]==-1)||(xPos+dx[i]==cols)) neighbors[i]=0;
			else neighbors[i]=&map[xyc((xPos+dx[i]),(yPos+dy[i]))];
		}
	}else cout<< "error! number of neighbors is not 4 or 8" << endl;
};

//Heuristic that reutns difference in coordinates. This assumes you can't move diagonally
//and that the cost to move between adjacent neighbors is always 1. (i.e. the map is not weighted)
float map_node::xyDiffHeur(map_node* pGoal){
	float dist;
	if(NUMNEIGHBS==4){
	dist = abs(xPos-(pGoal->xPos))+ abs(yPos-(pGoal->yPos));
	} else if(NUMNEIGHBS==8){
	float xdif = abs(xPos-(pGoal->xPos));
	float ydif = abs(yPos-(pGoal->yPos));
	float adj = abs(xdif-ydif);
	float square;
	if(xdif>ydif) square = xdif-adj;
	else square = ydif-adj;
	dist=square+adj;
	//first method often underestimated distance
//	float xdif = pow((xPos-(pGoal->xPos)),2);
//	float ydif = pow((yPos-(pGoal->yPos)),2);
//	dist = sqrt((xdif+ydif)/2);
//	}else{
//		cout<< "error! number of neighbors is not 4 or 8" << endl;
	}
	return dist;
};

//Fscore is based on the nodes gscore and its estimated distance to the goal
void map_node::calculateFScore(map_node goal, float (*Hueristic)(map_node)){
	fScore = gScore + Hueristic(goal);
	return;
};

//Function to set initial values of all nodes in the map
map_node* initMap(int rows, int cols){
	size_t s = sizeof(map_node)*rows*cols;
	map_node* map = new map_node[s];
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			map[i*cols+j].xPos=j;
			map[i*cols+j].yPos=i;
			map[i*cols+j].gScore = 0;
			map[i*cols+j].fScore = 999999999;
			map[i*cols+j].initNeighbors(rows, cols, map);
			map[i*cols+j].state = ' ';
		}
	}
	return map;
}

//Add randomly obstructed nodes to the world.
void randomizeTerrain(int rows, int cols, map_node* map, float pObs){
	int numObs=ceil(rows*cols*pObs-.5); //The total number of obstructed spaces
	while(numObs>0){
		int rx= rand()%(cols);
		int ry= rand()%(rows);
		//If the space is currently empty, make it obstructed and decrement the loop variable
		if(map[xyc(rx,ry)].state == ' ') {
			map[xyc(rx,ry)].state = 'O';
			numObs--;
		}
	}
	return;
}

void printMap(int rows, int cols, map_node* map){
	for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				switch (map[ijc(i,j)].state){
				case 'O':
					cout << "\u2588";
					break;
				case 'S':
					cout << 'S';
					break;
				case 'G':
					cout << 'G';
					break;
				case 'P':
					cout << "\u2591";
					break;
				default:
					if(map[ijc(i,j)].isClosed) cout << 'C';
					else if ((map[ijc(i,j)].isOpen)) cout <<'O';
					else cout << ' ';
					break;
				}
			}
			cout << endl;
	}
}

//Function I sometimes use in debugging to prompt user and wait for enter key to be pressed
void wait()
  {
  std::cout << "Press ENTER to continue...";
  std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
  }

//Prints out all of the nodes, their addresses and the address of their neighbors
void debugNeighbors(map_node* map){
	for(int y=0;y<NUMROWS;y++){
			for(int x=0;x<NUMCOLS;x++){
				//Print out current node
				cout<< '(' << x << ',' << y << "):" << '[' << map[xyc(x,y)].xPos << ',' << map[xyc(x,y)].yPos << ']' << "with address: "<< &map[xyc(x,y)] << endl;
				for(uint q=0; q<(sizeof(map[xyc(x,y)].neighbors)/sizeof(map[xyc(x,y)].neighbors[1])); q++){
					//Print null if there is no neighbor in a certain position
					if(map[xyc(x,y)].neighbors[q]==0){
						cout<< "   Has Neighbors #" << q << ": NULL" << endl;
						continue;
					}
					//Otherwise print the neighbors x,y location and address
					cout<< "   Has Neighbors #" << q << ": [" << map[xyc(x,y)].neighbors[q]->xPos << ',' << map[xyc(x,y)].neighbors[q]->yPos << ']' << "with address: "<< map[xyc(x,y)].neighbors[q] << endl;
				}
				//wait();
			}
		}
}

void forceResort(openQueue open_nodes){
	//This forces the queue to resort which may be necessary if the fScore of something already in the open queue changes
	if(!open_nodes.empty()){
	map_node* temp = open_nodes.top();
	open_nodes.pop();
	open_nodes.push(temp);
	}
	return;
}

map_node* deepCopyMap(int rows, int cols, map_node* map){
size_t s = sizeof(map_node)*rows*cols;
	map_node* mapCopy = new map_node[s];
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			mapCopy[ijc(i,j)].xPos = map[ijc(i,j)].xPos;
			mapCopy[ijc(i,j)].yPos = map[ijc(i,j)].yPos;
			mapCopy[ijc(i,j)].gScore = map[ijc(i,j)].gScore;
			mapCopy[ijc(i,j)].fScore = map[ijc(i,j)].fScore;
			mapCopy[ijc(i,j)].isOpen = map[ijc(i,j)].isOpen;
			mapCopy[ijc(i,j)].isClosed = map[ijc(i,j)].isClosed;
			mapCopy[ijc(i,j)].state = map[ijc(i,j)].state;
			mapCopy[ijc(i,j)].initNeighbors(rows, cols, mapCopy);
			if(map[ijc(i,j)].cameFrom == 0) mapCopy[ijc(i,j)].cameFrom =0;
			else{
				int cameFromXPos = map[ijc(i,j)].cameFrom->xPos;
				int cameFromYpos = map[ijc(i,j)].cameFrom->yPos;
				mapCopy[ijc(i,j)].cameFrom = &mapCopy[xyc(cameFromXPos, cameFromYpos)];
			}
			}
		}
	return mapCopy;
}

int aStar(int rows, int cols, map_node* map){
	openQueue open_nodes;
	map_node *current, *pStart, *pGoal;
	int tent_gScore;
	for(int i=0;i<rows*cols;i++){
		if(map[i].state == 'S'){
			pStart = &map[i];
			pStart->gScore =0;
			pStart->fScore = pStart->gScore + pStart->xyDiffHeur(pGoal);
			pStart->isOpen =1;
			open_nodes.push(pStart); //Only the start node is in the open_nodes queue at the start
		}
		if(map[i].state == 'G')pGoal=&map[i];
	}

	while(!open_nodes.empty()){
		//Print the map and wait for user to hit enter
		printMap(rows, cols, map);
		cout << endl;
		//wait();
		//Read the lowest fScore node off the top of the queue, then pop it off
		current=open_nodes.top();
		cout << "The fScore of the node being expanded is:" << current->fScore << endl;
		cout << "The gScore of the node being expanded is:" << current->gScore << endl;
		current->isOpen=0;
		current->isClosed=1;
		open_nodes.pop();
		//Finish if the current node is the goal
		if(current->state == 'G'){
			//Retrace the shortest path by traveling backwards using cameFrom pointers
			while(current->cameFrom->state != 'S'){
				current = current->cameFrom;
				current->state = 'P';
			}
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
}



