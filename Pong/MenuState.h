#pragma once
#include "GameState.h"

class MenuState :
	public GameState
{
public:
	~MenuState();
	static MenuState* getInstance(StateManager* pManager);
protected:
	MenuState(StateManager* pManager);
};

