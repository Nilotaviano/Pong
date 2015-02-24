#pragma once
class Bar
{
public:
	Bar(float xPosition, float yPosition);
	~Bar(void);
	static const float HALF_WIDTH;
	static const float HALF_HEIGHT;
	void moveLeft(int times);
	void moveRight(int times);
	void draw();
	float getX();
	float getY();
private:
	static const float STEP;
	float xPos_;
	float yPos_;
};

