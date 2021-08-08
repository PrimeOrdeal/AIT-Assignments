#pragma once
#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>
#include <string>

#include "assets.h"
#include "vector_2D.h"
#include "configuration.h"
#include "input.h"
#include "Circle_2D.h"
#include "scene.h"

class Game_Object
{
public:
	Game_Object(std::string id, std::string texture_id);
	~Game_Object();

	std::string id();
	Vector_2D translation();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) = 0;
	virtual void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config);
	virtual void set_texture(std::string textture_id);

	Circle_2D collider();

	void set_height(int height);
	void set_width(int width);
	void set_translation(Vector_2D translation);

	int height();
	int width();

protected:
	std::string _id;
	std::string _texture_id;

	Circle_2D _collider;

	Vector_2D _translation; // replaces _x and _y. Represents the current position of the Game Object.
	Vector_2D _velocity; // Represents the direction and speed the Game Object is moving.

	int _width;
	int _height;

	SDL_RendererFlip _flip;
};

