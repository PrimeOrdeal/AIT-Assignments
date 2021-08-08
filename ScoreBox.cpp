#pragma once

#include "ScoreBox.h"

ScoreBox::ScoreBox(std::string id) : Game_Object(id, "Texture.Dino")
{
	_translation = Vector_2D(50, 50);

	// Set the translation to the feet of the Game Object
	// and make the radius smaller than the actual Game Object.
	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));
}

ScoreBox::~ScoreBox()
{
}

void ScoreBox::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}