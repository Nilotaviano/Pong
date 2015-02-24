#pragma once

#include "GameState.h"

class StateManager
{
public:
	StateManager(bool* quit);
	~StateManager();

	void update(InputHandler inputHandler, int interval);
	void draw();
	void changeState(GameState* pNewState);
	GameState* getActiveState() { return pActiveState_; }
private:
	GameState* pActiveState_;
	bool* quit_;
};