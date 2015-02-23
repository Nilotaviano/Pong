#include "GameOverState.h"
#include "StateManager.h"
#include "PlayState.h"
#include "MenuState.h"

GameOverState::GameOverState(StateManager* pManager)
:GameState(pManager),
messageFont_(32, "fonts/game_over.TTF", 0, 0.15, 0, 0, 0),
playAgainButton_(-0.5f, -0.3f, 0.45f, 0.15f, 68, 118, 205, "Play again", 18),
menuButton_(0.0f, -0.3f, 0.55f, 0.15f, 68, 118, 205, "Quit to menu", 17)
{
	//TODO: Beautify this
	
	buttons.push_back(playAgainButton_);	
	buttons.push_back(menuButton_);
	current = buttons.begin();
	current._Ptr->_Myval.selected = true;
}


GameOverState::~GameOverState()
{
}

GameOverState* GameOverState::getInstance(StateManager* pManager)
{
	static GameOverState Instance(pManager);
	return &Instance;
}

void GameOverState::update(InputHandler inputHandler)
{
	if (inputHandler.isKeyPressed(SDLK_RETURN)) {
		pStateManager_->changeState(PlayState::getInstance(pStateManager_));
	}

	if (inputHandler.isKeyPressed(SDLK_a)) {
		current._Ptr->_Myval.selected = false;
		if (current != buttons.begin()) {
			current--;
			current._Ptr->_Myval.selected = true;
		}
		else {
			current = buttons.end(); //Returns iterator past the last element
			current--;	//Gets to the last element
			current._Ptr->_Myval.selected = true;
		}
	}

	if (inputHandler.isKeyPressed(SDLK_d)) {
		current._Ptr->_Myval.selected = false;
		if (++current == buttons.end()) {
			current = buttons.begin();
			current._Ptr->_Myval.selected = true;
		}
	}
}

void GameOverState::draw()
{
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