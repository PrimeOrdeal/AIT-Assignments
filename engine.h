#pragma once

#include "assets.h"
#include "scene.h"
#include "input.h"
#include "configuration.h"

#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>

class Engine
{
public:
	Engine(std::string window_name, Configuration* config);
	~Engine();

	void simulate(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene, Input* input, Configuration* config);

	SDL_Renderer*	renderer();
	SDL_Window*		window();

private:
	void simulate_AI(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene, Input* input);
	void simulate_physics(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene);
	void render(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene, Configuration* config);

	SDL_Window*		_window = NULL;
	SDL_Renderer*	_renderer = NULL;


	const int	_x = 100;
	const int	_y = 100;
	const int	_width = 600;
	const int	_height = 600;
};

