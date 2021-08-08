#pragma once
#include "game_object.h"


class Dragable_Object : public Game_Object
{
public:
	Dragable_Object(std::string id, std::string texture_id, float x, float y);
	~Dragable_Object();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};

