#pragma once
#include "Bar.h"
#include <math.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include "GameState.h"

class Ball
{
public:
	Ball(void);
	~Ball(void);
	GameState move(void);
	void draw();
	void detectCollision(Bar bar);
private:
	float xPos_;
	float yPos_;
	float ySpd_;
	float xSpd_;
	static const float MAX_SPEED;
	static const float MIN_SPEED_EACH_AXIS;
	static const float RADIUS;
	void setSpeed(float newXSpeed, float newYSpeed);
};

