#pragma once
#include <SDL.h>
#include "bar.h"

#define KEYBOARD_SIZE 256

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);
	void handleInput(SDL_Event event, bool *quit);
	bool isKeyPressed(SDL_Keycode key);
private:
	void handleKeyboard(SDL_KeyboardEvent kbEvent);
	bool keys_[KEYBOARD_SIZE];
};

