#include "Game.h"
#include "PlayState.h"
#include <stdio.h>
#include "font.h"

Game::Game()
: pSdlWindow_(nullptr), quit(false),
SCREEN_WIDTH(640), SCREEN_HEIGHT(480)
{
	pStateManager_ = new StateManager();
	pStateManager_->changeState(PlayState::getInstance(pStateManager_));
}

Game::~Game()
{
	delete(pStateManager_);
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


		//Create window
		pSdlWindow_ = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (pSdlWindow_ == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			SDL_GLContext glContext = SDL_GL_CreateContext(pSdlWindow_);
			if (glContext == nullptr)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Initialize clear color
	glClearColor(1.f, 1.f, 1.f, 0.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	return success;
}

void Game::close()
{
	//Destroy window	
	SDL_DestroyWindow(pSdlWindow_);
	pSdlWindow_ = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void Game::update() 
{
	pStateManager_->update(inputHandler_);
}

void Game::draw()
{
	pStateManager_->draw();
}

void Game::run() {
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		SDL_Event event;

		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&event) != 0)
			{
				inputHandler_.handleInput(event, &quit);
			}

			update();
			draw();

			//Update screen
			SDL_GL_SwapWindow(pSdlWindow_);
		}
	}

	//Free resources and close SDL
	close();
}