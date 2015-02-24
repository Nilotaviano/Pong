#include "Bar.h"
#include "Ball.h"
#include <stdio.h>
#include <math.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

const float Bar::HALF_WIDTH = 0.1f;
const float Bar::HALF_HEIGHT = 0.025f;
const float Bar::STEP = 0.001f;


Bar::Bar(float xPosition, float yPosition)
{
	const float STEP = 0.00075f;
	xPos_ = xPosition;
	yPos_ = yPosition;
}


Bar::~Bar(void)
{
}


void Bar::moveLeft(int times)
{
	//Can't go out of the screen
	for (int i = 0; i < times; i++) {
		if (xPos_ > -1 + HALF_WIDTH) {
			xPos_ -= STEP;
		}
	}
}


void Bar::moveRight(int times)
{
	//Can't go out of the screen
	for (int i = 0; i < times; i++) {
		if (xPos_ < 1 - HALF_WIDTH) {
			xPos_ += STEP;
		}
	}
}

void Bar::draw(void) {
	glColor3f(0, 0, 1);
	glRectd(
		(xPos_ + -HALF_WIDTH),
		(yPos_ + -HALF_HEIGHT),
		(xPos_ + HALF_WIDTH),
		(yPos_ + HALF_HEIGHT)
		);
}

float Bar::getX() {
	return xPos_;
}

float Bar::getY() {
	return yPos_;
}