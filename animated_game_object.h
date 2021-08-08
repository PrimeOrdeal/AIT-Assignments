#pragma once

#include "game_object.h"

class Animated_Game_Object : public Game_Object
{
public:
	Animated_Game_Object(std::string id, std::string texture_id, float x, float y, Vector_2D* velocity);
	~Animated_Game_Object();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;


};


