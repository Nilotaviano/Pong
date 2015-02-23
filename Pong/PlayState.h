#pragma once
#include "Ball.h"
#include "Bar.h"
#include "InputHandler.h"
#include "EnumGamePlayState.h"
#include "GameState.h"
#include "StateManager.h"

class PlayState : 
	public GameState
{
public:
	~PlayState();
	void update(InputHandler inputHandler);
	void draw();
	static PlayState* getInstance(StateManager* pManager);
	void leaveState();

protected:
	PlayState(StateManager* pManager);
private:
	Ball ball;
	Bar bar1;
	Bar bar2;
};

