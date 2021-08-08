#pragma once

#include "dino.h"

Dino::Dino(std::string id) : Game_Object(id, "Texture.Title")
{
	_translation = Vector_2D(300, 0);
	_width = 200;
	_height = 100;

	// Set the translation to the feet of the Game Object
	// and make the radius smaller than the actual Game Object.
	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));
}

Dino::~Dino()
{
}

void Dino::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}