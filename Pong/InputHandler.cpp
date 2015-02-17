#include "InputHandler.h"

InputHandler::InputHandler(void)
{
	for(int i = 0 ; i < KEYBOARD_SIZE ; i++) {
		keyboard[i] = false;
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
		handleKey(event.key);
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

void InputHandler::handleKey(SDL_KeyboardEvent kbEvent) {
	int key = kbEvent.keysym.sym;

	if(key < KEYBOARD_SIZE) {
		switch (kbEvent.type){
		case SDL_KEYUP:
			keyboard[kbEvent.keysym.sym] = false;
			break;
		case SDL_KEYDOWN:
			keyboard[kbEvent.keysym.sym] = true;
			break;
		}
	}
}

void InputHandler::updateBar(Bar *bar) {
	if(keyboard[SDLK_a]) {
		(*bar).moveLeft();
	}
	if(keyboard[SDLK_d]) {
		(*bar).moveRight();
	}
}