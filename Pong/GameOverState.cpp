#include "GameOverState.h"
#include "StateManager.h"
#include "PlayState.h"
#include "MenuState.h"

GameOverState::GameOverState(StateManager* pManager)
:GameState(pManager),
messageFont_(32, "fonts/game_over.TTF", 0, 0.15f, 0, 0, 0),
playAgainButton_(-0.5f, -0.3f, 0.45f, 0.15f, 68, 118, 205, "Play again", 18),
menuButton_(0.0f, -0.3f, 0.55f, 0.15f, 68, 118, 205, "Quit to menu", 17)
{
	//TODO: Beautify this
	playAgainButton_.selected = true;
	timeBuffer_ = 0;
}

GameOverState::~GameOverState()
{
}

GameOverState* GameOverState::getInstance(StateManager* pManager)
{
	static GameOverState Instance(pManager);
	return &Instance;
}

void GameOverState::update(InputHandler inputHandler, int interval)
{
	timeBuffer_ += interval;

	if (inputHandler.isKeyPressed(SDLK_RETURN)) {
		if (playAgainButton_.selected) {
			pStateManager_->changeState(PlayState::getInstance(pStateManager_));
		}
		else {
			pStateManager_->changeState(MenuState::getInstance(pStateManager_));
		}
	}

	if (timeBuffer_ > 150) {
		if (inputHandler.isKeyPressed(SDLK_a)) {
			if (playAgainButton_.selected) {
				playAgainButton_.selected = false;
				menuButton_.selected = true;
			}
			else {
				playAgainButton_.selected = true;
				menuButton_.selected = false;
			}
			timeBuffer_ = 0;
		}

		if (inputHandler.isKeyPressed(SDLK_d)) {
			if (playAgainButton_.selected) {
				playAgainButton_.selected = false;
				menuButton_.selected = true;
			}
			else {
				playAgainButton_.selected = true;
				menuButton_.selected = false;
			}
			timeBuffer_ = 0;
		}

	}
}

void GameOverState::draw()
{
  int blendSrc;
  int blendDst;
  glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrc);
  glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDst);

  glClear(GL_COLOR_BUFFER_BIT);

  PlayState::getInstance(pStateManager_)->draw();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
  glRectf(-1, -1, 1, 1);

  glBlendFunc(blendSrc, blendDst);

	playAgainButton_.draw();
	menuButton_.draw();
	messageFont_.draw();
}

void GameOverState::setWinner(Winner winner)
{
	switch (winner)
	{
	case PLAYER_1:
		messageFont_.setText("Player 1 wins!");
		break;
	case PLAYER_2:
		messageFont_.setText("Player 2 wins!");
		break;
	default:
		break;
	}
}