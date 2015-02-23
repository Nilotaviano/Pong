#include "PlayState.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "GameOverState.h"
#include "EnumGamePlayState.h"

PlayState::PlayState(StateManager* pManager)
:GameState(pManager),
bar1(0.0f, -0.90f), bar2(0.0f, 0.90f)
{
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

	if (gamePlayState != NOT_OVER) {
		GameOverState* gameOverState = GameOverState::getInstance(pStateManager_);
		if (gamePlayState == PLAYER1_WINS) {
			gameOverState->setWinner(PLAYER_1);
		}
		else {
			gameOverState->setWinner(PLAYER_2);
		}
		pStateManager_->changeState(gameOverState);
	}
}

void PlayState::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ball.draw();
	bar1.draw();
	bar2.draw();
}

void PlayState::leaveState() {
	ball = Ball::Ball();
	bar1 = Bar::Bar(0.0f, -0.90f);
	bar2 = Bar::Bar(0.0f, 0.90f);
}