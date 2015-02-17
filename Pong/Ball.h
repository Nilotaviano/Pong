#pragma once
#include "Bar.h"
#include <math.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

class Ball
{
public:
	enum gameState
	{
		PLAYER1_WINS = 1,
		PLAYER2_WINS = -1,
		NOT_OVER = 0
	};
	Ball(void);
	~Ball(void);
	int move(void);
	void draw();
	void detectCollision(Bar bar);
private:
	float xPos;
	float yPos;
	float ySpd;
	float xSpd;
	static const float MAX_SPEED;
	static const float RADIUS;
	void setSpeed(float newXSpeed, float newYSpeed);
};

