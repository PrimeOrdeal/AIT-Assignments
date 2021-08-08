#pragma once
#include "dragable_object.h"


Dragable_Object::Dragable_Object(std::string id, std::string texture_id, float x, float y) : Game_Object(id, texture_id)
{
	// Set position on screen
	_translation = Vector_2D(x, y);

	// set width and height
	_width	= 75; 
	_height = 75;

	// Set the translation to the feet of the Game Object
	// and make the radius smaller than the actual Game Object.
	//_collider.set_radius(_width / 5.0f);
	//_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));
}

Dragable_Object::~Dragable_Object()
{
}

void Dragable_Object::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}