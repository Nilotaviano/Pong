#include "GameState.h"
#include "StateManager.h"


GameState::GameState(StateManager* pManager)
: pStateManager_(pManager)
{
}


GameState::~GameState()
{
}

void GameState::changeState(GameState* pNewGameState) {
	pStateManager_->changeState(pNewGameState);
}