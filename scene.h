#pragma once

#include <map>
#include <string>
#include <vector>

#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>

// Forward declaration of the Game_Object class - this prevents circular inclusion that would occur if we used #include "game_object.h"
class Game_Object; 

// A scene is also known as a map or a level.
class Scene
{
public:
	Scene(std::string id);
	~Scene();

	virtual void update(SDL_Window* window) = 0;

	Game_Object* get_game_object(std::string id);
	std::vector<Game_Object*> get_game_objects();

	std::string id();

protected:
	std::map<std::string, Game_Object*> _game_objects;
	std::string							_id;
};

