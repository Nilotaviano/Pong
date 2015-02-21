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
	pActiveState_ = pNewGameState;
}

void StateManager::update(InputHandler inputHandler)
{
	if (pActiveState_) {
		pActiveState_->update(inputHandler);
	}

}

void StateManager::render() 
{
	if (pActiveState_) {
		pActiveState_->render();
	}
}