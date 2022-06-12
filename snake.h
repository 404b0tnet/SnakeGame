/*
file:	snake.h
by:		Justin Smith
org:	COP 2001, Spring 2020
for:	Header file a snake class object
*/

#pragma once

#include "snakedefs.h"
#include "block.h"


class Snake {

private:
	Block head;				// root of the snake body

	Block* tail;			// pointer to last block in body

	Block previousTail;		// erasing and appending 

	Block speed;			// traveling velocity in x/y axis

	int size;				// number of body blocks in snake

	Direction current;		// current direction snake is traveling
	Direction next;			// direction player has inputed

public:

	//----------------------------------------------
	// Constructors
	//----------------------------------------------
	Snake();
	Snake(int startColumn, int startRow);


	//----------------------------------------------
	// Accessors
	//----------------------------------------------
	Block* getHead();
	Block* getTail();
	Block* getPreviousTail();
	int getSize();
	Direction getCurrentDirection();
	Direction getNextDirection();


	//----------------------------------------------
	// Methods
	//----------------------------------------------
	void setDirections(int input);
	void turn();
	void move();
	bool isMoving();

};	// end class Snake