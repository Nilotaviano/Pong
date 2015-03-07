#pragma once
#include <SDL.h>
#include <functional>

#include "bar.h"

#define KEYBOARD_SIZE 256

class Game;

class InputHandler
{
public:
  InputHandler(bool* quit, std::function<void()> resize_function);
	~InputHandler(void);
	void handleInput(SDL_Event event);
	bool isKeyPressed(SDL_Keycode key);
private:
  std::function<void()> p_resize_function_;
  bool* p_quit_;
	void handleKeyboard(SDL_KeyboardEvent kbEvent);
	bool keys_[KEYBOARD_SIZE];
};
