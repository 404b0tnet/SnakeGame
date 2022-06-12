/*
file:	snakedefs.h
by:		Justin Smith
org:	COP 2001, Spring 2020
for:	Global configuration data for the snake game
*/

#pragma once

#include "console.h"

//-----------------------------------------------------------------------------
// Global Constants and Data Structures
//-----------------------------------------------------------------------------
const int WIDTH = 50;
const int SCREEN_HEIGHT = 50;		// Size of console
const int SCALE = 10;

const int START_X = 25;
const int START_Y = 25;

const Color BACKGROUND_COLOR = Black;
const Color	SNAKE_COLOR = White;
const Color	FOOD_COLOR = Red;


enum Direction
{
	None = 0,
	Left,
	Right,
	Up,
	Down,
	Quit = -1
};