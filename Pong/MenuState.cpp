#include "MenuState.h"


MenuState::MenuState(StateManager* pManager)
: GameState(pManager),
playButton_		(0.0f, 0.5f, 0.4f, 0.25f, 0, 20, 168, "Play", 20),
optionsButton_	(0.0f, 0.0f, 0.4f, 0.25f, 0, 20, 168, "Options", 20)
quitButton_		(0.0f,-0.5f, 0.4f, 0.25f, 0, 20, 168, "Quit", 20)
{
	//TODO: Beautify this
	playButton_.selected = true;
	timeBuffer_ = 0;
}


MenuState::~MenuState()
{
}

MenuState* MenuState::getInstance(StateManager* pManager)
{
	static MenuState Instance(pManager);
	return &Instance;
}

void MenuState::leaveState() 
{
	
}
void MenuState::update(InputHandler inputHandler, int interval)
{
	timeBuffer_ += interval;

	if (inputHandler.isKeyPressed(SDLK_RETURN)) {
		if (playAgainButton_.selected) {
			pStateManager_->changeState(PlayState::getInstance(pStateManager_));
		}
		else if(optionsButton_.selected) {
			//TODO Options
		} 
		else if(quitButton_.selected) {
			pStateManager_->quit();
		}
	}

	if (timeBuffer_ > 150) {
		if (inputHandler.isKeyPressed(SDLK_w)) {
			if (playAgainButton_.selected) {
				playAgainButton_.selected = false;
				menuButton_.selected = true;
			}
			else {
				playAgainButton_.selected = true;
				menuButton_.selected = false;
			}
			timeBuffer_ = 0;
		}

		if (inputHandler.isKeyPressed(SDLK_s)) {
			if (playAgainButton_.selected) {
				playAgainButton_.selected = false;
				menuButton_.selected = true;
			}
			else {
				playAgainButton_.selected = true;
				menuButton_.selected = false;
			}
			timeBuffer_ = 0;
		}

	}
}
void MenuState::draw()
{
		
}