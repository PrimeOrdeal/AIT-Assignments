#pragma once

#include <map>

#include "texture.h"
#include "animated_texture.h"
#include "Asset.h"
#include "Sound.h"


class Assets
{
public:
	Assets(SDL_Renderer* renderer);
	~Assets();

	Asset* get_asset(std::string id);
	

private:
	// Make an array of Texture pointers, indexed by string
	std::map<std::string, Asset*> _assets;

};

