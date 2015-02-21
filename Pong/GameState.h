#pragma once

#include "InputHandler.h"

class StateManager;

class GameState
{
public:
	GameState(StateManager* pManager);
	~GameState();
	virtual void render() {}
	virtual void update(InputHandler inputHandler) {}
	void changeState(GameState* pNewGameState);

private :
	StateManager* pStateManager_;
};