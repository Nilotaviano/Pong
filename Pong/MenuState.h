#pragma once
#include "GameState.h"

class MenuState :
	public GameState
{
public:
	~MenuState();
	static MenuState* getInstance(StateManager* pManager);
	void leaveState();
	void update(InputHandler inputHandler, int interval);
	void draw();
protected:
	MenuState(StateManager* pManager);
};

