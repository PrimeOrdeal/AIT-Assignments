#pragma once

// using SDL
#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>

class Game
{
public:
	Game();

	// @brief	creates the renderer
	//			Initial allocation of the objects are done here
	bool Start();

	// @brief	handles any user input that has happened since the last call
	void ProcessInput();

	// @brief	advances the game simulation, it runs AI, Physics, player movement
	void Update();

	// @brief	draws the game so the player can see what happened
	void Draw();

	// @brief	deallocates the objects created
	void ShutDown();

	// @brief	Set the value of title in the Game object
	void SetTitle(char* title);

	// @brief	creates a window and begin the game loop
	//			it first calls the start once and after it is successful
	//			it calls the ProcessInput(), Update() and Draw() funcitons in the game loop
	//			and ends with the calling of Shutdown() after the game loop has ended.
	// @param title - title for the window
	// @param width - width of the window
	// @param height - height of the window
	// @param fullscreen - enables or disables fullscreen for the window
	void Run(int width, int height, bool fullscreen);

	// @brief	delete the window and the renderer when closing the application
	//			shutdown the SDL framework
	void Destroy();

	~Game();
private:
	// the window we will be rendering to
	SDL_Window* _sdlWindow;
	// 2D rendering context for a window
	SDL_Renderer* _sdlRenderer;
	// flag for the game loop
	bool _isGameOver;
	// create a variable to hold the Window title
	char* _title;
};

