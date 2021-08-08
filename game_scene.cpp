#pragma once

#include "game_scene.h"
#include "dino.h"
#include "Player.h"
#include "animated_game_object.h"
#include "portal_entry.h"
#include "portal_exit.h"
#include "dragable_object.h"

Game_Scene::Game_Scene() : Scene("Game")
{
	Vector_2D* left_to_right_velocity = new Vector_2D(0.02f,0.0f); //(left-to-right, up-to-down)
	Vector_2D* right_to_left_velocity = new Vector_2D(-0.02f, 0.0f);
	Game_Object* dino_walking_1 = new Animated_Game_Object("Dino.Walking1", "Texture.Dino.Walking", 50, 100, left_to_right_velocity);
	_game_objects[dino_walking_1->id()] = dino_walking_1;

	Game_Object* dino_walking_2 = new Animated_Game_Object("Dino.Walking2", "Texture.Dino.Walking", 650, 200, right_to_left_velocity);
	_game_objects[dino_walking_2->id()] = dino_walking_2;

	Game_Object* dino_walking_3 = new Animated_Game_Object("Dino.Walking3", "Texture.Dino.Walking", 50, 300, left_to_right_velocity);
	_game_objects[dino_walking_3->id()] = dino_walking_3;

	Game_Object* dino_walking_4 = new Animated_Game_Object("Dino.Walking4", "Texture.Dino.Walking", 650, 400, right_to_left_velocity);
	_game_objects[dino_walking_4->id()] = dino_walking_4;

	Game_Object* dino_walking_5 = new Animated_Game_Object("Dino.Walking5", "Texture.Dino.Walking", 50, 500, left_to_right_velocity);
	_game_objects[dino_walking_5->id()] = dino_walking_5;

	// Handcuffs
	Game_Object* handcuffs = new Dragable_Object("Handcuffs", "Texture.Handcuffs", 0, 700);
	_game_objects[handcuffs->id()] = handcuffs;

	// Syringe
	Game_Object* syringe = new Dragable_Object("Syringe", "Texture.Syringe", 700, 700);
	_game_objects[syringe->id()] = syringe;

	// Title
	Game_Object* title = new Dino("Title");
	_game_objects[title->id()] = title;

	//Game_Object* player_walking = new Player("Player.Walking");
	//_game_objects[player_walking->id()] = player_walking;

	//Game_Object* portal_entry = new Portal_Entry();
	//_game_objects[portal_entry->id()] = portal_entry;

	//Game_Object* portal_exit = new Portal_Exit();
	//_game_objects[portal_exit->id()] = portal_exit;

}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{
}
