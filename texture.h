#pragma once
#include <iostream>
#include "Asset.h"


#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>
#include <string>

class Texture : public Asset
{
public:
	Texture(std::string id, std::string path, SDL_Renderer* renderer);
	~Texture();

	SDL_Texture* data();

	virtual void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip);

private:
	SDL_Texture* _data = nullptr;
};

