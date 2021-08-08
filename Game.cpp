#include "Game.h"

#include <iostream>

// default constructor
Game::Game()
{
	// set the SDL window pointer to null
	_sdlWindow = nullptr;
	// set the SDL renderer pointer to null
	_sdlRenderer = nullptr;
	// set the_title pointer to null
	_title = nullptr;

	// intialise SDL
	// if the intialisation was not successful
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		// disable the game loop
		_isGameOver = true;
		// print a failed message on to the console window
		std::cout << "Initialise SDL - failed" << std::endl;
	}
	// if the initialisation was successful
	else
	{
		// enable the game loop
		_isGameOver = false;
		// print a success messag on to the console window
		std::cout << "Initialise SDL - success" << std::endl;
	}
}

bool Game::Start()
{
	// create the renderer for the window created.
	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (_sdlRenderer != nullptr)
	{
		std::cout << "Create Renderer - success" << std::endl;
		// TODO: Initialise objects here

		return true;
	}
	std::cout << "Create Renderer - failed" << std::endl;
	return false;
}

void Game::Run(int width, int height, bool fullscreen)
{
	// maintain the creation flag
	int creationFlag = 0;

	// if the full screen is set to false, set to windowed mode
	if (!fullscreen)
	{
		creationFlag = SDL_WINDOW_SHOWN;
	}
	// if true, set to full screen mode
	else
	{
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}

	// create the SDL window
	_sdlWindow = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
								width, height, 
								creationFlag);

	// if the Window has been created successfully
	// create the renderer and start the game loop
	if (_sdlWindow != nullptr && Start())
	{
		// debug message if the window has been successfully created
		std::cout << "Create Window - success" << std::endl;
		// start the game loop
		while (!_isGameOver)
		{
			// checks for input from the input
			ProcessInput();

			// any changes to the AI, physics or player movement
			Update();

			// draws on the window
			Draw();
		}
	}
	else
	{
		// debug message if the window failed to be created
		std::cout << "Create Window - failed" << std::endl; 
	}

	// clean up
	ShutDown();
	Destroy();
}

void Game::Draw()
{
	// set the Draw colour to black
	SDL_SetRenderDrawColor(_sdlRenderer, 0, 0, 0, 255);
	// clears the render colour with the colour set above
	SDL_RenderClear(_sdlRenderer);
	// SDL_Renderer* draws to the hidden target.
	// This function will take everything on the hidden target and draw it to the window connected to the renderer
	SDL_RenderPresent(_sdlRenderer);

	// TODO: draw your stuff here
}

// Destroy() destroys the Window and the Renderer created
void Game::Destroy()
{
	// deallocates the SDL_Window*
	SDL_DestroyWindow(_sdlWindow);
	// deallocates the SDL_renderer*
	SDL_DestroyRenderer(_sdlRenderer);
	// shuts down the SDL framework
	SDL_Quit();
}

void Game::ProcessInput()
{
	// TODO: Get the user input here
}

void Game::Update()
{
	// TODO: update your stuff here
}

void Game::ShutDown()
{
	// TODO: deallocate the stuff you created in Start()
}

void Game::SetTitle(char* title)
{
	_title = title;
}

// destructor
Game::~Game()
{

}
