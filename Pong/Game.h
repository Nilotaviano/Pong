#pragma once

#include "StateManager.h"
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	void update();
	void render();
	void run();
private:
	bool init();
	bool initGL();
	void close();
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Window* pSdlWindow_;
	StateManager* pStateManager_;
	InputHandler inputHandler_;
	bool quit;
};