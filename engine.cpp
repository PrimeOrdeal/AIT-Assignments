#pragma once
#include "engine.h"
#include "texture.h"
#include "animated_texture.h"
#include "game_object.h"

// used for std::sort
#include <algorithm>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Engine::Engine(std::string window_name, Configuration* config)
{
	int SDL_init_return_value		= SDL_Init(SDL_INIT_EVERYTHING);
	const int init_result_success	= 0;
	if (SDL_init_return_value != init_result_success)
	{
		std::cout << "Unable to intialise SDL - Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	else
		std::cout << "SDL Initialised!" << std::endl;

	const char* _game_title = window_name.c_str();
	_window = SDL_CreateWindow(_game_title, _x, _y, config->window_width, config->window_width, SDL_WINDOW_RESIZABLE);
	if (_window == nullptr)
	{
		std::cout << "Failed to create SDL window" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int first_renderer = -1;
	_renderer = SDL_CreateRenderer(_window, first_renderer, SDL_RENDERER_ACCELERATED);	
	if (_renderer == nullptr)
	{
		std::cout << "Failed to create Renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int ttf_init_result = TTF_Init();
	const int ttf_init_success = 0;
	if (ttf_init_result != ttf_init_success)
	{
		std::cout << "Failed to initalise SDL TTF" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int image_init_result = IMG_Init(IMG_INIT_PNG);
	const int image_init_success = IMG_INIT_PNG;
	if (image_init_result != image_init_success)
	{
		std::cout << "Failed to initialize SDL Image" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int mixer_init_result = Mix_Init(MIX_INIT_MOD);
	const int mixer_init_failure = 0;
	if (mixer_init_result == mixer_init_failure)
	{
		std::cout << "Failed to initialize SDL Mixer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		std::cout << "Mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}

	const int mixer_open_audio_result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	const int mixer_open_audio_success = 0;
	if (mixer_open_audio_result != mixer_open_audio_success)
	{
		std::cout << "Failed to open audio" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	Mix_AllocateChannels(3);

}

Engine::~Engine()
{
	SDL_DestroyWindow(_window);
}

SDL_Window* Engine::window()
{
	return _window;
}


void Engine::render(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Configuration* config)
{
	// Clear Renderer
	// The backbuffer should be considered invalidated after each SDL_RenderPresent().
	// Do not assume that previous contents will exist between frames.
	int renderer_clear_result	= SDL_RenderClear(_renderer);
	bool renderer_clear_failed	= renderer_clear_result != 0;
	if (renderer_clear_failed)
	{
		std::cout << "Failed to clear renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const Uint8 red		= 200;
	const Uint8 green	= 200;
	const Uint8 blue	= 50;
	const Uint8 alpha	= 255;

	// Set the color used for drawing operations
	int draw_color_result	= SDL_SetRenderDrawColor(_renderer, red, green, blue, alpha);
	bool draw_color_failed	= draw_color_result != 0;
	if (draw_color_failed)
	{
		std::cout << "Failed to draw colour" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	std::vector<Game_Object*> sorted_game_objects = scene->get_game_objects();
	const struct
	{
		bool operator()(Game_Object* a, Game_Object* b)
		{
			return a->translation().y() < b->translation().y();
		}
	} sort_by_y_order;
	std::sort(sorted_game_objects.begin(), sorted_game_objects.end(), sort_by_y_order);

	for (Game_Object* game_object : sorted_game_objects)
	{
		game_object->render(milliseconds_to_simulate, assets, _renderer, config);
	}


	// Inform SDL we are finished our rendering and it can now present to the window.
	// Update the screen with any rendering performed since the previous call.
	SDL_RenderPresent(_renderer);
}

SDL_Renderer* Engine::renderer()
{
	return _renderer;
}

void Engine::simulate(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene, Input* input, Configuration* config)
{
	Engine::simulate_AI(milliseconds_to_similate, assets, scene, input);
	Engine::simulate_physics(milliseconds_to_similate, assets, scene);
	Engine::render(milliseconds_to_similate, assets, scene, config);
}

void Engine::simulate_AI(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene, Input* input)
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	for (Game_Object* game_object : game_objects)
	{
		game_object->simulate_AI(milliseconds_to_similate, assets, input, scene);
	}
}

void Engine::simulate_physics(Uint32 milliseconds_to_similate, Assets* assets, Scene* scene)
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	for (Game_Object* game_object : game_objects)
	{
		game_object->simulate_physics(milliseconds_to_similate, assets, scene);
	}
}

