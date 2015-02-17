#include "Ball.h"

const float Ball::MAX_SPEED = 0.00005f;
const float Ball::RADIUS = 0.02f;

Ball::Ball(void)
{
	xPos = 0.0f;
	yPos = 0.0f;
	setSpeed(0.4f, -0.5f);
}

Ball::~Ball(void)
{
}

int Ball::move(void)
{
	xPos += xSpd;
	yPos += ySpd;

	//Checks if the ball is out of bounds on the X axis
	if(!(xPos - RADIUS > -1 && xPos + RADIUS < 1))
	{
		xSpd = -xSpd;	//Speed along X axis is inverted
	}

	if(yPos + RADIUS >= 1) {
		return gameState::PLAYER1_WINS;
	}
	else if(yPos - RADIUS <= -1) {
		gameState::PLAYER2_WINS;
	}
	else {
		return gameState::NOT_OVER;
	}
}

//Checks if the resulting speed will surpass the maximum speed, if it does, will limit it to the maximum speed and maintain proportion between speeds along both axes
void Ball::setSpeed(float newXSpeed, float newYSpeed) {
	float totalSpeed = sqrt(pow(newXSpeed, 2) + pow(newYSpeed, 2));
	if(totalSpeed > MAX_SPEED)
	{
		float cosDelta = newXSpeed/totalSpeed;
		float sinDelta = newYSpeed/totalSpeed;
		xSpd = MAX_SPEED * cosDelta;
		ySpd = MAX_SPEED * sinDelta;
	}
	else
	{
		xSpd = newXSpeed;
		ySpd = newYSpeed;
	}
}

void Ball::draw() {
	int triangleAmount = 25; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * 3.1415926f;


	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2d(xPos, yPos); // center of circle
	for(int i = 0; i <= triangleAmount;i++) { 
		glVertex2d(
			xPos + (RADIUS * cos(i *  twicePi / triangleAmount)), 
			yPos + (RADIUS * sin(i * twicePi / triangleAmount))
			);
	}
	glEnd();
}

void Ball::detectCollision(Bar bar) {
	float barX1, barX2, barY1, barY2;	//left, right, bottom, top
	float ballX1, ballX2, ballY1, ballY2;

	barX1 = bar.getX() - bar.HALF_WIDTH;
	barX2 = bar.getX() + bar.HALF_WIDTH;
	barY1 = bar.getY() - bar.HALF_HEIGHT;
	barY2 = bar.getY() + bar.HALF_HEIGHT;

	ballX1 = this->xPos - RADIUS;
	ballX2 = this->xPos + RADIUS;
	ballY1 = this->yPos - RADIUS;
	ballY2 = this->yPos + RADIUS;

	//Ball's sides are between the bar's left and right sides
	if(ballX1 > barX1 && ballX2 < barX2) {
		//Collision on top or bottom of the bar
		if((ballY1 > barY1 && ballY1 < barY2) ||
			(ballY2 > barY1 && ballY2 < barY2)) 
		{
			this->ySpd = -this->ySpd;
		}
		return;
	}

	//Ball's top and bottom are between the bar's top and bottom
	if(ballY1 > barY1 && ballY2 < barY2) {
		//Collision on the left or right side of the bar
		if((ballX2 > barX1 && ballX2 < barX2) ||
			(ballX1 < barX2 && ballX1 > barX1)) 
		{
			this->xSpd = -this->xSpd;
		}
		return;
	}
	//TODO fix this:
	//Corner (This will treat the ball as a RADIUS x RADIUS square)
	if(((ballX1 < barX1 && ballX2 > barX1) ||
		(ballX1 < barX2 && ballX2 > barX2)) &&
		((ballY1 < barY1 && ballY2 > barY1) ||
		(ballY1 < barY2 && ballX2 > barY2)))
	{
		if(ballX1 < barX1 && ballX2 > barX1) {//Corner on the left
			if(xSpd < 0) {
				setSpeed(xSpd * 1.5, -ySpd * 0.8f);
			}
			else {
				setSpeed(-xSpd * 0.8, -ySpd * 0.8f);
			}
		}
		else if(ballX1 < barX2 && ballX2 > barX2) {//Corner on the right
			if(xSpd > 0) {
				setSpeed(xSpd * 1.5, -ySpd * 0.8f);
			}
			else {
				setSpeed(-xSpd * 0.8, -ySpd * 0.8f);
			}
		}
		return;
	}
}