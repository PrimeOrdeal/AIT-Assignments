#pragma once

#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>

#include "texture.h"
#include "Asset.h"
#include "vector_2D.h"

class Text : public Asset
{
public:
	Text(SDL_Renderer* renderer, const char* text, SDL_Color color, std::string id);
	~Text();

	void render(SDL_Renderer* renderer, Vector_2D translation);

private:
	SDL_Texture* _data;
};

