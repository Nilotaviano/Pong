#pragma once
class Bar
{
public:
	Bar(float xPosition, float yPosition);
	Bar();
	~Bar(void);
	static const float HALF_WIDTH;
	static const float HALF_HEIGHT;
	void moveLeft(void);
	void moveRight(void);
	void draw();
	float getX();
	float getY();
private:
	static const float STEP;
	float xPos;
	float yPos;
};

