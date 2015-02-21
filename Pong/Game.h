#pragma once
#include "Ball.h"
#include "Bar.h"
#include "InputHandler.h"
#include "GameState.h"


class Game
{
public:
	Game();
	~Game();
	bool play(SDL_Window* gWindow);
private:
	Ball ball;
	Bar bar1;
	Bar bar2;
	bool quit;
	InputHandler inputHandler;
	GameState update(); //Per frame update
	void render();
};

