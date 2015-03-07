#include "Game.h"

#include <stdio.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include "MenuState.h"
#include "font.h"

Game::Game()
: pSDLWindow_(nullptr), quit(false),
SCREEN_WIDTH(640), SCREEN_HEIGHT(480),
inputHandler_(&quit, std::bind(&Game::resize, this))
{
	pStateManager_ = new StateManager(&quit);
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
		pSDLWindow_ = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (pSDLWindow_ == nullptr)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			SDL_GLContext glContext = SDL_GL_CreateContext(pSDLWindow_);
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
  int x, y;

  SDL_GetWindowSize(pSDLWindow_, &x, &y);
  glViewport(0, 0, x, y);

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
	SDL_DestroyWindow(pSDLWindow_);
	pSDLWindow_ = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void Game::update() 
{
	pStateManager_->update(inputHandler_, currentFrameTime - previousFrameTime);
}

void Game::draw()
{
	pStateManager_->draw();
}

void Game::resize()
{
  int w, h;
  float aspectRatio;
  SDL_GetWindowSize(pSDLWindow_, &w, &h);

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glOrtho(0, w, 0, h, -1, 1);

  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Game::run() {
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		SDL_Event event;
		currentFrameTime = SDL_GetTicks();
		previousFrameTime = currentFrameTime;

    pStateManager_->changeState(MenuState::getInstance(pStateManager_));

		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&event) != 0)
			{
				inputHandler_.handleInput(event);
			}

			if (SDL_GetTicks() - previousFrameTime > 0) {
				currentFrameTime = SDL_GetTicks();
				update();
				draw();
				previousFrameTime = currentFrameTime;
			}

			//Update screen
			SDL_GL_SwapWindow(pSDLWindow_);
		}
	}

	//Free resources and close SDL
	close();
}