#pragma once

#include "GameState.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	void update(InputHandler inputHandler);
	void render();
	void changeState(GameState* pNewState);
	GameState* getActiveState() { return pActiveState_; }

private:
	GameState* pActiveState_;
};