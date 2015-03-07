#pragma once
#include "GameState.h"

#include "Button.h"

class MenuState :
	public GameState
{
public:
	~MenuState();
	static MenuState* getInstance(StateManager* pManager);
  void enterState();
	void update(InputHandler inputHandler, int interval);
	void draw();
  void resize();

protected:
	MenuState(StateManager* pManager);
private:
	Button playButton_;
	Button optionsButton_;
	Button quitButton_;
  int timeBuffer_;
};

