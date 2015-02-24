#include "Button.h"
#include <SDL_opengl.h>


Button::Button(float x, float y, float width, float height, int r, int g, int b, char* text, int font_size)
: font_(text, font_size, "fonts/game_over.TTF", x + width / 2, y + height / 2, 255, 255, 255)
{
	selected = false;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;

	color_.r = r;
	color_.g = g;
	color_.b = b;

	textColor_.r = 255;
	textColor_.g = 255;
	textColor_.b = 255;
}

Button::~Button()
{
}

void Button::draw() {
	float outLineOffSet = 0.02f;
	if (selected) {
		glColor3ub(0, 0, 255);
		glRectf(
			x_ - outLineOffSet,
			y_ - outLineOffSet,
			x_ + width_ + outLineOffSet,
			y_ + height_ + outLineOffSet);
	}
	else {
		glColor3ub(255, 255, 255);
		glRectf(
			x_ - outLineOffSet,
			y_ - outLineOffSet,
			x_ + width_ + outLineOffSet,
			y_ + height_ + outLineOffSet);
	}

	glColor3i(color_.r, color_.g, color_.b);
	glRectf(
		x_,
		y_,
		x_ + width_,
		y_ + height_);

	font_.draw();
}