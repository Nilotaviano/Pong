#include "InputHandler.h"
#include <stdio.h>

InputHandler::InputHandler(void)
{
	for (int i = 0; i < KEYBOARD_SIZE; i++) {
		keys_[i] = false;
	}
}

InputHandler::~InputHandler(void)
{
}

void InputHandler::handleInput(SDL_Event event, bool *quit)
{
	switch (event.type)
	{
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		handleKeyboard(event.key);
		break;
	case SDL_MOUSEMOTION:
		break;
	case SDL_QUIT:
		*quit = true;
		break;
	default:
		printf("Unhandled Event: %i\n", event.type);
		break;
	}
}

void InputHandler::handleKeyboard(SDL_KeyboardEvent kbEvent)
{
	int key = kbEvent.keysym.sym;

	if (key < KEYBOARD_SIZE) {
		switch (kbEvent.type){
		case SDL_KEYUP:
			keys_[kbEvent.keysym.sym] = false;
			break;
		case SDL_KEYDOWN:
			keys_[kbEvent.keysym.sym] = true;
			break;
		}
	}
}

bool InputHandler::isKeyPressed(SDL_Keycode key)
{
	if (key < KEYBOARD_SIZE) {
		return keys_[key];
	} 
	else {
		return false;
	}
}