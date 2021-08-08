#pragma once

#include "game_object.h"

class ScoreBox : public Game_Object
{
public:
	ScoreBox(std::string id);
	~ScoreBox();

	virtual void simulate_AI(Uint32 milliseconds_ti_simulate, Assets* assets, Input* input, Scene* scene) override;
};
