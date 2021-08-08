#include "animated_game_object.h"

Animated_Game_Object::Animated_Game_Object(std::string id, std::string texture_id, float x, float y, Vector_2D* velocity) : Game_Object(id, texture_id)
{
	_translation = Vector_2D(x, y);
	_velocity = *velocity; // speed of x movement (+ = left to right, - = right to left)
}

Animated_Game_Object::~Animated_Game_Object()
{
}

void Animated_Game_Object::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Animated_Game_Object::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}

