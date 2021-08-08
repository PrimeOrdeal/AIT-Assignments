#pragma once

#define SDL_MAIN_HANDLED //must always include this when including SDL.h!!
#include <SDL.h>

#include "texture.h"
#include "Asset.h"
class Animated_Texture : public Texture
{
public:
	Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds);
	~Animated_Texture();

	void update_frame(Uint32 milliseconds_to_simulate);
	// Added override as we will not use the render method inherited from Texture:
	void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip) override; 

private:
	int			_frame_count;
	Uint32		_frame_duration_milliseconds;
	Uint32		_total_time_milliseconds;
	int			_current_frame;
	//Texture*	_data; //removed because we now inherit this from Texture
};

