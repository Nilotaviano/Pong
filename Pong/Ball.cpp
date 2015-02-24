#include "Ball.h"

const float Ball::MAX_SPEED = 0.0006f;
const float Ball::MIN_SPEED_EACH_AXIS = 0.0001f;
const float Ball::RADIUS = 0.02f;

Ball::Ball(void)
{
	xPos_ = 0.0f;
	yPos_ = 0.0f;
	setSpeed(0.4f, -0.5f);
}

Ball::~Ball(void)
{
}

GamePlayState Ball::move(int times)
{
	xPos_ += xSpd_;
	yPos_ += ySpd_;

	//Checks if the ball is out of bounds on the X axis
	if (!(xPos_ - RADIUS > -1 && xPos_ + RADIUS < 1))
	{
		xSpd_ = -xSpd_;	//Speed along X axis is inverted
	}

	if (yPos_ + RADIUS >= 1) {
		return PLAYER1_WINS;
	}
	else if (yPos_ - RADIUS <= -1) {
		PLAYER2_WINS;
	}
	else {
		return NOT_OVER;
	}
}

//Checks if the resulting speed will surpass the maximum speed, if it does, will limit it to the maximum speed and maintain proportion between speeds along both axes
void Ball::setSpeed(float newXSpeed, float newYSpeed) {
	float totalSpeed;

	if (abs(newXSpeed) < MIN_SPEED_EACH_AXIS) {
		newXSpeed = newXSpeed >= 0 ? MIN_SPEED_EACH_AXIS : -MIN_SPEED_EACH_AXIS;
	}
	if (abs(newYSpeed) < MIN_SPEED_EACH_AXIS) {
		newYSpeed = newYSpeed >= 0 ? MIN_SPEED_EACH_AXIS : -MIN_SPEED_EACH_AXIS;
	}

	totalSpeed = sqrt(pow(newXSpeed, 2) + pow(newYSpeed, 2));

	if (totalSpeed > MAX_SPEED)
	{
		float cosDelta = newXSpeed / totalSpeed;
		float sinDelta = newYSpeed / totalSpeed;
		xSpd_ = MAX_SPEED * cosDelta;
		ySpd_ = MAX_SPEED * sinDelta;
	}
	else
	{
		xSpd_ = newXSpeed;
		ySpd_ = newYSpeed;
	}
}

void Ball::draw() {
	int triangleAmount = 25; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * 3.1415926f;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2d(xPos_, yPos_); // center of circle
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2d(
			xPos_ + (RADIUS * cos(i *  twicePi / triangleAmount)),
			yPos_ + (RADIUS * sin(i * twicePi / triangleAmount))
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

	ballX1 = this->xPos_ - RADIUS;
	ballX2 = this->xPos_ + RADIUS;
	ballY1 = this->yPos_ - RADIUS;
	ballY2 = this->yPos_ + RADIUS;

	//Ball hit the top or bottom of a bar
	if ((ballX1 > barX1 && ballX2 < barX2) &&
		((ballY1 > barY1 && ballY1 < barY2) ||
		(ballY2 > barY1 && ballY2 < barY2))) 
	{
		this->ySpd_ = -this->ySpd_;
		return;
	}

	//Ball hit one side of a bar
	if ((ballY1 > barY1 && ballY2 < barY2) &&
		((ballX2 > barX1 && ballX2 < barX2) ||
		(ballX1 < barX2 && ballX1 > barX1))) 
	{
		this->xSpd_ = -this->xSpd_;
		return;
	}

	//TODO fix this:
	//Corner (This will treat the ball as a RADIUS x RADIUS square)
	if (((ballX1 < barX1 && ballX2 > barX1) ||
		(ballX1 < barX2 && ballX2 > barX2)) &&
		((ballY1 < barY1 && ballY2 > barY1) ||
		(ballY1 < barY2 && ballX2 > barY2)))
	{
		if (ballX1 < barX1 && ballX2 > barX1) {//Corner on the left
			if (xSpd_ < 0) {
				setSpeed(xSpd_ * 1.5f, -ySpd_ * 0.8f);
			}
			else {
				setSpeed(-xSpd_ * 0.8f, -ySpd_ * 0.8f);
			}
		}
		else if (ballX1 < barX2 && ballX2 > barX2) {//Corner on the right
			if (xSpd_ > 0) {
				setSpeed(xSpd_ * 1.5f, -ySpd_ * 0.8f);
			}
			else {
				setSpeed(-xSpd_ * 0.8f, -ySpd_ * 0.8f);
			}
		}
		return;
	}
}