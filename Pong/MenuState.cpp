#include "MenuState.h"


MenuState::MenuState(StateManager* pManager)
: GameState(pManager)
{
}


MenuState::~MenuState()
{
}

MenuState* MenuState::getInstance(StateManager* pManager)
{
	static MenuState Instance(pManager);
	return &Instance;
}