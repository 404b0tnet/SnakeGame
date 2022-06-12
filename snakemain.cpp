/*
file:	snakemain.cpp
by:		Justin Smith
org:	COP 2001, Spring 2020
for:	Snake Game
*/

#include <iostream>
#include <time.h>		// time
#include <stdlib.h>		// srand, rand
#include "snake.h"


using namespace std;




// **************************
// function prototype
// **************************
void update(Snake& snake, Block& food);
bool collisionCheck(Snake& snake);
void render(HDC hdc, Snake snake, Block food);
Block nextFood(Snake snake);
bool collideSnake(Snake snake, Block check, bool includeHead);



int main() {						// Start main

	HDC console = initConsole(WIDTH, SCREEN_HEIGHT, SCALE);

	drawBorders(console, WIDTH, SCREEN_HEIGHT, SCALE, White);
	drawBorders(console, WIDTH, SCREEN_HEIGHT, SCALE, White);

	// initialize random numbers
	srand(time(NULL));

	Snake snake = Snake(START_X, START_Y);

	// current food location
	Block food = nextFood(snake);




	// main game loop
	do {

		// process player input
		if (snake.getNextDirection() == None)
			snake.setDirections(getGameKeys());


		// update game objects
		if (snake.getNextDirection() != Quit)
			update(snake, food);


		// draw the game
		render(console, snake, food);
		

		Sleep(.05 * 1000);			// pause 5th of a second


	} while (snake.getNextDirection() != Quit); // game main loop


	drawBorders(console, WIDTH, SCREEN_HEIGHT, SCALE, White);

	return 0;
}// End main


/********************************************************

update game objects
parameters:
	snake	-	(out)	snake structure
	food	-	(out)	food block

returns:
	void

********************************************************/
void update(Snake& snake, Block& food){
	
	if (snake.getNextDirection() != None) {
		snake.turn();
	}

	// see if snake has started moving yet
	if (snake.isMoving()) {
		snake.move();		// move
	}

	// did we eat food
	if (Snake::head.Column == food.Column && head.Row == food.Row) {
		
		// increase snake size
		snake.sizeOfSnake++;

		// add old tail location at new body index
		snake.body[snake.sizeOfSnake - 1] = snake.tail;

		// make tail empty so we don't erase it
		snake.tail = EMPTY_BLOCK;

		// make food empty so we get new food
		food = EMPTY_BLOCK;

	}
	// collision check
	else if(collisionCheck(snake))
		snake.nextDirection = Quit;


	// if food is empty, we get new food
	if(food.Column == EMPTY_BLOCK.Column)
		food = nextFood(snake);


	return;
}



/********************************************************
checks if the snake hits any walls or itself
parameters:
	snake	-	(out)	snake structure

returns:
	bool	-	true if collision occurred
********************************************************/
bool collisionCheck(Snake& snake) {
	bool collision = false;

	Block head = snake.body[0];

	// Horizontal
	if (head.Column <= 0) {
		collision = true;
		head.Column = 0;
	}
	else if (head.Column >= WIDTH) {
		collision = true;
		head.Column = WIDTH - 1;
	};

	// Vertical
	if (head.Row < 0) {
		collision = true;
		head.Row = 0;
	}
	else if (head.Row > SCREEN_HEIGHT) {
		collision = true;
		head.Row = SCREEN_HEIGHT - 1;
	};

	// check if snake hit itself
	if (collideSnake(snake, head, false)) {
		collision = true;
	}

	// if collision then update head
	if (collision) {
		snake.body[0] = head;
	}
	
	return collision;
}



/********************************************************
draw a snake block on the console window
parameters:
	hdc		-	handle to the console window for drawing
	snake	-	snake structure
	food	-	current food block

returns:
	void
********************************************************/
void render(HDC hdc, Snake snake, Block food) {

	// draw food block
	draw(hdc, food.Column, food.Row, SCALE, FOOD_COLOR);

	// erase previous tail of snake
	draw(hdc, snake.tail.Column, snake.tail.Row, SCALE, BACKGROUND_COLOR);

	// draw head at new position
	draw(hdc, snake.body[0].Column, snake.body[0].Row, SCALE, SNAKE_COLOR);

	return;
}


/********************************************************

generate random location for new food
parameters:
	snake	-	snake structure

returns:
	Block	-	location of next food

********************************************************/
Block nextFood(Snake snake) {
	Block food = EMPTY_BLOCK;

	while (food.Column == EMPTY_BLOCK.Column) {

		// (x,y) position of food
		food.Column = rand() % WIDTH;
		food.Row = rand() % SCREEN_HEIGHT;

		// check if snake occupies food location
		if (collideSnake(snake, food, true))
			food = EMPTY_BLOCK;		// set food to empty

	}

	return food;

}



/********************************************************

see if snake collides with a block
parameters:
	snake		-	snake structure
	check		-	block to check for collision with
	includeHead	-	true if head of snake should be checked

returns:
	bool	-	true if collides

********************************************************/
bool collideSnake(Snake snake, Block check, bool includeHead) {
	bool collide = false;

	int i = 0;
	if (!includeHead)
		i++;		// skip checking head block

	while (i < snake.sizeOfSnake && !collide) {
		Block part = snake.body[i];

		if (part.Column == check.Column && part.Row == check.Row)
			collide = true;
		i++;
	}

	return collide;
}