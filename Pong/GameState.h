#pragma once

#include "InputHandler.h"

class StateManager;

class GameState
{
public:
	GameState(StateManager* pManager);
	~GameState();
	virtual void draw() {}
	virtual void update(InputHandler inputHandler) {}
	void changeState(GameState* pNewGameState);
	virtual void leaveState() {}

protected:
	StateManager* pStateManager_;
};