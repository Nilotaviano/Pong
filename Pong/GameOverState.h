#pragma once
#include "GameState.h"
#include "Font.h"
#include "Button.h"
#include <list>


typedef enum Winner {PLAYER_1, PLAYER_2};

class GameOverState :
	public GameState
{
public:
	~GameOverState();
	void update(InputHandler inputHandler, int interval);
	void draw();
	static GameOverState* getInstance(StateManager* pManager);
	void setWinner(Winner winner);

protected:
	GameOverState(StateManager* pManager);
private:
	Winner winner_;
	Font messageFont_;
	Button menuButton_;
	Button playAgainButton_;
	int timeBuffer;
};