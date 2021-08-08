#pragma once

#include "portal_entry.h"
#include "scene.h"

Portal_Entry::Portal_Entry()
	: Game_Object("Portal.Entry", "Texture.Portal.Entry")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(50, 300);
}

Portal_Entry::~Portal_Entry()
{

}
void Portal_Entry::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Portal_Entry::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	// Get player object from scene
	Game_Object* player = scene->get_game_object("Player.Walking");

	// Calculate portal center
	Vector_2D portal_center = _translation + Vector_2D((float)_width/2, (float)_height/2);

	// Calculate player center
	Vector_2D player_center = player->translation()	+ Vector_2D((float)player->width()/2, (float)player->height()/2);
	
	// Get distance from portal center to player center
	float distance_to_player = (portal_center - player_center).magnitude();
	
	// If distance is less than some tolerance, i.e. they are in the trigger region
	if (distance_to_player < 50.0f)
	{
		// If triggered, teleport to some exit position
		Game_Object* portal_exit = scene->get_game_object("Portal.Exit");
		Vector_2D portal_exit_location = portal_exit->translation()
			+ Vector_2D(100.f, 0.f);

		// Set player translation to exit position
		player->set_translation(portal_exit_location);
	}
}