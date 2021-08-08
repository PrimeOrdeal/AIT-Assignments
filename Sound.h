#pragma once

#include"Asset.h"

#include <SDL_mixer.h>

class Sound : public Asset
{
public:
	Sound(std::string id, std::string path);
	~Sound();

	Mix_Chunk* data();

private:
	Mix_Chunk* _data;
};

