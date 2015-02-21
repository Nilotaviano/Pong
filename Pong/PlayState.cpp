#include "PlayState.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "EnumGamePlayState.h"

PlayState::PlayState(StateManager* pManager)
:GameState(pManager),
bar1(0.0f, -0.90f), bar2(0.0f, 0.90f)
{
	quit = false;
}

PlayState::~PlayState()
{

}

PlayState* PlayState::getInstance(StateManager* pManager)
{
	static PlayState Instance(pManager);
	return &Instance;
}

void PlayState::update(InputHandler inputHandler)
{
	GamePlayState gamePlayState;
	ball.detectCollision(bar1);
	ball.detectCollision(bar2);

	if (inputHandler.isKeyPressed(SDLK_a)) {
		bar1.moveLeft();
	}
	if (inputHandler.isKeyPressed(SDLK_d)) {
		bar1.moveRight();
	}

	gamePlayState = ball.move();
}

void PlayState::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ball.draw();
	bar1.draw();
	bar2.draw();
}