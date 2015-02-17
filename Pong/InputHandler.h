#pragma once
#include <SDL.h>
#include <stdio.h>
#include "bar.h"

#define KEYBOARD_SIZE 256
class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);
	bool keyboard[KEYBOARD_SIZE];
	void handleInput(SDL_Event event, bool *quit);
	void updateBar(Bar *bar);
private:
	void handleKey(SDL_KeyboardEvent kbEvent);
};

