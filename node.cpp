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


void randomizeTerrain(int rows, int cols, map_node* map, float pObs){
	int numObs=ceil(rows*cols*pObs+.5); //The total number of obstructed spaces
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
				default:
					cout << ' ';
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
				for(int q=0; q<4; q++){
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


