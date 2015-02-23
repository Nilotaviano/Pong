#pragma once
#include <SDL.h>
#include "Font.h"

class Button
{
public:
	Button(float x, float y, float width, float height, int r, int g, int b, char* text, int font_size);
	~Button();
	void draw();
	bool selected;
private:
	float x_;
	float y_;
	float width_;
	float height_;
	SDL_Color color_;
	SDL_Color textColor_;
	Font font_;
};