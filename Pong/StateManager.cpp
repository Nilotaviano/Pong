#include "StateManager.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

StateManager::StateManager(bool* quit) 
: pActiveState_(NULL),
bool* quit_(quit)
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

void StateManager::update(InputHandler inputHandler, int interval)
{
	if (pActiveState_) {
		pActiveState_->update(inputHandler, interval);
	}

}

void StateManager::draw() 
{
	if (pActiveState_) {
		pActiveState_->draw();
	}
}

void StateManager::quit() 
{
	*quit_ = true;
}