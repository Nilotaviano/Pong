#include "StateManager.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

StateManager::StateManager() : pActiveState_(NULL)
{
}


StateManager::~StateManager()
{
}

void StateManager::changeState(GameState* pNewGameState) 
{
	if (pActiveState_ != nullptr) {
		pActiveState_->leaveState();
	}
	pActiveState_ = pNewGameState;
}

void StateManager::update(InputHandler inputHandler)
{
	if (pActiveState_) {
		pActiveState_->update(inputHandler);
	}

}

void StateManager::draw() 
{
	if (pActiveState_) {
		pActiveState_->draw();
	}
}