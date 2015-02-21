#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "Game.h"

Game::Game()
:bar1(0.0f, -0.90f), bar2(0.0f, 0.90f)
{
	quit = false;
}

Game::~Game() {

}

GameState Game::update() {
	GameState gameState;

	ball.detectCollision(bar2);
	inputHandler.updateBar(&bar1);
	gameState = ball.move();
	ball.detectCollision(bar1);

	return gameState;
}

void Game::render() {
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	ball.draw();
	bar1.draw();
	bar2.draw();
	glFlush();
}

bool Game::play(SDL_Window* gWindow) {
	//Event handler
	SDL_Event event;
	GameState gameState = GameState::NOT_OVER;

	while (!quit && gameState == GameState::NOT_OVER)
	{
		//Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			inputHandler.handleInput(event, &quit);
		}

		gameState = update();
		render();

		//Update screen
		SDL_GL_SwapWindow(gWindow);
	}

	if (quit) {
		return false;
	}
	else {
		char op;
		printf("Gostaria de jogar novamente? (S/N)");
		scanf_s("%c", &op); getchar();
		switch (op) {
		case 'S':
		case 's':
			return true;
			break;
		case 'N':
		case 'n':
			return false;
			break;
		default:
			return false;
			break;
		}
	}
}