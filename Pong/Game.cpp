#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "Ball.h"
#include "Bar.h"
#include "InputHandler.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Per frame update
void update(Ball *ball, Bar *bar1, Bar *bar2, InputHandler inputHandler);

//Renders quad to the screen
void render(Ball ball, Bar bar1);

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
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
		gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if(gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if(SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if(!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Initialize clear color
	glClearColor(1.f, 1.f, 1.f, 0.f);

	//Check for error
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	return success;
}

void update(Ball *ball, Bar *bar1, Bar *bar2, InputHandler inputHandler)
{
	(*ball).move();
	(*ball).detectCollision((*bar1));
	(*ball).detectCollision((*bar2));
	inputHandler.updateBar(bar1);
}

void render(Ball ball, Bar bar1, Bar bar2)
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	ball.draw();
	bar1.draw();
	bar2.draw();
	glFlush();
}

void close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Ball ball;
	Bar bar1 = Bar::Bar(0.0f, -0.90f);
	Bar bar2 = Bar::Bar(0.0f, 0.90f);
	InputHandler inputHandler;

	//Start up SDL and create window
	if(!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;
		int x = 0, y = 0;
		bool toggleKey = false;
		//Event handler
		SDL_Event event;

		//Enable text input

		//While application is running
		while(!quit)
		{
			//Handle events on queue
			while(SDL_PollEvent(&event) != 0)
			{
				inputHandler.handleInput(event, &quit);
			}

			update(&ball, &bar1, &bar2, inputHandler);
			render(ball, bar1, bar2);

			//Update screen
			SDL_GL_SwapWindow(gWindow);
		}

		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	close();

	return 0;
}