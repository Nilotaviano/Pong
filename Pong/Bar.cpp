#include "Bar.h"
#include "Ball.h"
#include <stdio.h>
#include <math.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

const float Bar::HALF_WIDTH = 0.1f;
const float Bar::HALF_HEIGHT = 0.025f;
const float Bar::STEP = 0.00025f;


Bar::Bar(float xPosition, float yPosition)
{
	const float STEP = 0.00075f;
	xPos = xPosition;
	yPos = yPosition;
}


Bar::~Bar(void)
{
}


void Bar::moveLeft(void)
{
	//Can't go out of the screen
	if(xPos > -1 + HALF_WIDTH) {
		xPos -= STEP;
	}
}


void Bar::moveRight(void)
{
	//Can't go out of the screen
	if(xPos < 1 - HALF_WIDTH) {
		xPos += STEP;
	}
}

void Bar::draw(void) {
	glColor3f(0, 0, 1);
	glRectd(
		(xPos + -HALF_WIDTH),
		(yPos + -HALF_HEIGHT),
		(xPos + HALF_WIDTH),
		(yPos + HALF_HEIGHT)
		);
}

float Bar::getX() {
	return xPos;
}

float Bar::getY() {
	return yPos;
}