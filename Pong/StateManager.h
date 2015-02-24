#pragma once

#include "GameState.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	void update(InputHandler inputHandler, int interval, bool* quit);
	void draw();
	void changeState(GameState* pNewState);
	GameState* getActiveState() { return pActiveState_; }

private:
	GameState* pActiveState_;
};