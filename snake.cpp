/*
file:	snake.cpp
by:		Justin Smith
org:	COP 2001, Spring 2020
for:	Implementation file for a snake class object
*/

#include "snake.h"

//----------------------------------------------
// Constructors
//----------------------------------------------
/********************************************************
Default constructor of an empty snake where all variables
zero of null
parameters:
returns:

********************************************************/
Snake::Snake() {
	head = Block();				// root of the snake body
	tail = &head;				// tail points ot current head
	previousTail = Block();		// no previous tail (empty) 

	speed = Block(0,0);			// speed = 0
	size =1 ;					// number of body blocks in snake

	current = None;				// not moving
	next = None;				// no player input
}

/********************************************************
Set a new snake with head at a starting column and row
parameters:
	startColumn		- x coordinate for head
	startRow		- y coordinate for head
returns:
********************************************************/
Snake::Snake(int startColumn, int startRow) {
	head = Block(startColumn, startRow);		// root of the snake body
	tail = &head;								// tail points ot current head
	previousTail = Block();						// empty previous tail
	previousTail.copy(tail);					// set same as tail

	speed = Block(0, 0);						// speed = 0
	size = 1;									// number of body blocks in snake

	current = None;								// not moving
	next = None;								// no player input
}


//----------------------------------------------
// Accessors
//----------------------------------------------
/********************************************************
Returns a pointer to the head of the snake
parameters:
returns:
	Block*	- head block
********************************************************/
Block* Snake::getHead() {
	return &head;

}

/********************************************************
Returns a pointer to the tail of the snake
parameters:
returns:
	Block*	- tail block
********************************************************/
Block* Snake::getTail() {
	return tail;
}

/********************************************************
Returns a pointer to the previous tail of the snake
parameters:
returns:
	Block*	- previous tail block
********************************************************/
Block* Snake::getPreviousTail() {
	return &previousTail;
}

/********************************************************
Returns current size of snake in block
parameters:
returns:
	int - size of snake
********************************************************/
int Snake::getSize() {
	return size;
}

/********************************************************
Returns current direction snake is moving
parameters:
returns:
	Direction	-	current direction enum, None or Quit
********************************************************/
Direction Snake::getCurrentDirection() {
	return current;
}

/********************************************************
Returns next direction snake is moving based on user input
parameters:
returns:
	Direction	-	current direction enum, None or Quit
********************************************************/
Direction Snake::getNextDirection() {
	return next;
}


//----------------------------------------------
// Methods
//----------------------------------------------
/********************************************************
Set the next direction for the snake based on player input
parameters:
	input	- console keyboard code
returns:
	void
********************************************************/
void Snake::setDirections(int input) {


	switch (input) {
	case VK_A:					// Move left
	case VK_LEFT:
		if (current != Left && current != Right)
			next = Left;
		break;
	case VK_D:					// Move right
	case VK_RIGHT:
		if (current != Left && current != Right)
			next = Right;
		break;
	case VK_W:					// Move up
	case VK_UP:
		if (current != Up && current != Down)
			next = Up;
		break;
	case VK_S:					// Move down
	case VK_DOWN:
		if (current != Up && current != Down)
			next = Down;
		break;
	case VK_X:					// Escape key
	case VK_ESCAPE:
		next = Quit;
		break;
	default:					// No valid input
		next = None;
	}	// end of switch

	return;
}


/********************************************************
Adjust speed of snake based on directions to turn
the snake
parameters:
returns:
	void
********************************************************/
void Snake::turn() {

	current = next;			// update directions
	next = None;

	switch (current) {
	case Left:
		speed.setColumn(-1);
		speed.setRow(0);
		break;
	case Right:
		speed.setColumn(1);
		speed.setRow(0);
		break;
	case Up:
		speed.setColumn(0);
		speed.setRow(-1);
		break;
	case Down:
		speed.setColumn(0);
		speed.setRow(1);
		break;
	}	// end of switch

	return;
}

/********************************************************
Move snake based on its speed
parameters:
returns:
	void
********************************************************/
void Snake::move() {

	previousTail.copy(tail);		// save previous tail position

	// move up snake from tail to head copying x,y coordinates
	// from block in front to current block
	Block* temp = tail;
	while (temp) {

		// if block in front of this one
		if (temp->getForward()) 
			// then copy it's values to this one
			temp->copy(temp->getForward());
		
		// move temp point forward in snake
		temp->getForward();
	};

	// adjust snake head for speed
	head.setColumn(head.getColumn() + speed.getColumn());
	head.setRow(head.getRow() + speed.getRow());

	return;
}

/********************************************************
Determine if the snake has a non-zero speed set
parameters:
returns:
	bool	- true if speed is not zero
********************************************************/
bool Snake::isMoving() {
	Block zero = Block(0, 0);
	return !speed.equals(zero);
}