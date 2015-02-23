#include "Font.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

int round(double x)
{
	return (int)(x + 0.5);
}

int nextpoweroftwo(int x)
{
	double logbase2 = log((float)x) / log(2.0f);
	return round(pow(2, ceil(logbase2)));
}

Font::Font(char* text, int size, char* fontpath, float x, float y, int r, int g, int b) :
size_(size),
text_(text)
{
	int vPort[4];
	if (TTF_Init())
		printf(TTF_GetError());
	atexit(TTF_Quit);

	if (!(font_ = TTF_OpenFont(fontpath, size_))) {
		printf("Error loading font_: %s", TTF_GetError());
	}

	glGetIntegerv(GL_VIEWPORT, vPort);
	screenWidth_ = vPort[2];
	screenHeight_ = vPort[3];

	x_ = (int)x >= 0 ?
		screenWidth_ / 2 + x * screenWidth_ / 2 :
		screenWidth_ / 2 - x * screenWidth_ / 2;
	y_ = (int)y >= 0 ?
		screenHeight_ / 2 + y * screenHeight_ / 2 :
		screenHeight_ / 2 - y * screenHeight_ / 2;

	color_.r = r;
	color_.g = g;
	color_.b = b;
}

Font::Font(int size, char* fontpath, float x, float y, int r, int g, int b) :
size_(size)
{
	int vPort[4];

	if (TTF_Init())
		printf(TTF_GetError());
	atexit(TTF_Quit);

	if (!(font_ = TTF_OpenFont(fontpath, size_))) {
		printf("Error loading font_: %s", TTF_GetError());
	}
	text_ = "No text set";

	glGetIntegerv(GL_VIEWPORT, vPort);
	screenWidth_ = vPort[2];
	screenHeight_ = vPort[3];

	x_ = (int)x >= 0 ?
		screenWidth_ / 2 + x * screenWidth_ / 2 :
		screenWidth_ / 2 - x * screenWidth_ / 2;
	y_ = (int)y >= 0 ?
		screenHeight_ / 2 + y * screenHeight_ / 2 :
		screenHeight_ / 2 - y * screenHeight_ / 2;

	color_.r = r;
	color_.g = g;
	color_.b = b;
}

Font::Font(char* text, int size, char* fontpath) :
text_(text),
size_(size_)
{
	if (TTF_Init())
		printf(TTF_GetError());
	atexit(TTF_Quit);

	if (!(font_ = TTF_OpenFont("fontpath", size_))) {
		printf("Error loading font_: %s", TTF_GetError());
	}
}

Font::Font(int size, char* fontpath) :
size_(size)
{
	if (TTF_Init())
		printf(TTF_GetError());
	atexit(TTF_Quit);

	if (!(font_ = TTF_OpenFont(fontpath, size_))) {
		printf("Error loading font_: %s", TTF_GetError());
	}
	text_ = "No text set";
}

Font::~Font()
{
}

void Font::setText(char* text) {
	text_ = text;
}

void Font::SDL_GL_RenderText()
{
	SDL_Surface *initial;
	SDL_Surface *intermediary;
	int w, h;
	int texture;

	/* Use SDL_TTF to draw our text */
	initial = TTF_RenderText_Blended(font_, text_, color_);

	if (initial == nullptr) {
		printf("initial null");
		getchar();
	}

	/* Convert the rendered text to a known format */
	w = initial->w;
	h = initial->h;

	printf("W: %d\nH: %d\n\n", w, h);

	intermediary = SDL_CreateRGBSurface(0, w, h, 32,
		0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(initial, 0, intermediary, 0);

	/* Tell GL about our new texture */
	glGenTextures(1, ((GLuint*)&texture));
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, intermediary->pixels);

	/* GL_NEAREST looks horrible, if scaled... */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* prepare to draw our texture */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);

	/* Draw a quad at location */
	glBegin(GL_QUADS);
	/* Recall that the origin is in the lower-left corner
	That is why the TexCoords specify different corners
	than the Vertex coors seem to. */
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x_ - w/2, y_ - h/2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x_ + w/2, y_ - h/2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x_ + w/2, y_ + h/2);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x_ - w/2, y_ + h/2);
	glEnd();

	/* Bad things happen if we delete the texture before it finishes */
	glFinish();

	/* Clean up */
	SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, ((GLuint*)&texture));
}

void Font::glEnable2D()
{
	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	//printf("x: %i\ny: %i\nw: %i\nh: %i\n", vPort[0], vPort[1], vPort[2], vPort[3]);

	screenWidth_ = vPort[2];
	screenHeight_ = vPort[3];

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Font::glDisable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Font::draw(float x, float y, int r, int g, int b)
{
	/* Go in HUD-drawing mode */
	glEnable2D();

	/* Draw some text */
	color_.r = 0;
	color_.g = 0;
	color_.b = 0;

	x_ = (int) x >= 0 ? 
		screenWidth_ / 2 + x * screenWidth_ / 2 : 
		screenWidth_ / 2 - x * screenWidth_ / 2;
	y_ = (int) y >= 0 ? 
		screenHeight_ / 2 + y * screenHeight_ / 2 : 
		screenHeight_ / 2 - y * screenHeight_ / 2;


	SDL_GL_RenderText();

	glDisable2D();
	glDisable(GL_TEXTURE_2D);
}

void Font::draw()
{
	/* Go in HUD-drawing mode */
	glEnable2D();

	SDL_GL_RenderText();

	glDisable2D();
	glDisable(GL_TEXTURE_2D);
}