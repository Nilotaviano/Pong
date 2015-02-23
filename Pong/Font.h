#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

/*
Source:
http://www.gamedev.net/topic/284259-for-reference-using-sdl_ttf-with-opengl/
*/

class Font
{
public:
	Font(char* text, int size, char* fontpath, float x, float y, int r, int g, int b);
	Font(int size, char* fontpath, float x, float y, int r, int g, int b);
	Font(char* text, int size, char* fontpath);
	Font(int size, char* fontpath);
	~Font();
	void draw(float x, float y, int r, int g, int b);
	void draw();
	void setText(char * text);
private:
	void SDL_GL_RenderText();
	void glEnable2D();
	void glDisable2D();

	char *text_;
	TTF_Font* font_;
	SDL_Color color_;
	int size_;
	int screenWidth_;
	int screenHeight_;
	float x_;
	float y_;
};

