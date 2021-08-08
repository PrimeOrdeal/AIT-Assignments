#include "animated_texture.h"

// Texture(id,path,renderer) will call the base class constructor when the Animated_Texture object is created.
Animated_Texture::Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds) : Texture(id, path, renderer)
{
	_frame_count					= frame_count;
	_frame_duration_milliseconds	= frame_duration_milliseconds;
	_total_time_milliseconds		= frame_duration_milliseconds;
	_current_frame					= 0;
}

Animated_Texture::~Animated_Texture()
{
}


void Animated_Texture::update_frame(Uint32 milliseconds_to_simulate)
{
	// Calculate: which frame should be rendered to the user. 
	// This can be calculated by the (culuminative time / the frame_duration) to get how many frames have passed. 
	// This can be moduloed with the frame count to provide the exact frame to be rendered.
	_total_time_milliseconds += milliseconds_to_simulate;
	_current_frame = (_total_time_milliseconds / _frame_duration_milliseconds) % _frame_count;
	//std::cout << "_current_frame = " << _current_frame << std::endl;
}

void Animated_Texture::render(SDL_Renderer* renderer, SDL_Rect*, SDL_Rect* destination, SDL_RendererFlip flip)
{
	// Render: the current frame by calculating the clip coordinates of the texture.
	// Calculate texture width.
	int texture_w = 0;
	int texture_h = 0;
	const int query_success = 0;
	const int query_texture_result = SDL_QueryTexture(data(), nullptr, nullptr, &texture_w, &texture_h);

	if (query_texture_result != query_success)
	{
		std::cout << "Failed to query animated texture image. " << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Calculate frame width (texture width / frame count).
	const int frame_w = texture_w / _frame_count;

	SDL_Rect frame_clip;
	frame_clip.x = _current_frame * frame_w;
	frame_clip.y = 0;
	frame_clip.w = frame_w;		// set clip to be the width of the frame
	frame_clip.h = texture_h;	// set clip to be the height of the frame

	// Render texture using clipping rect. Updated to call Base class render function
	Texture::render(renderer, &frame_clip, destination, flip);
}

