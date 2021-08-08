#include "texture.h"

#include <SDL_image.h>

// Asset(id) will call the base class constructor when the Texture object is created.
Texture::Texture( std::string id,std::string path, SDL_Renderer* renderer) : Asset(id)
{
	SDL_Surface* surface = nullptr;
	if (path.find("bmp") != std::string::npos)
	{
		surface = SDL_LoadBMP(path.c_str());
	}
	else if (path.find("png") != std::string::npos)
	{
		surface = IMG_Load(path.c_str());
	}
	else
	{
		std::cout << "Unknown image file extension. Path: " << path << std::endl;
		exit(1);
	}

	_data = SDL_CreateTextureFromSurface(renderer, surface);

	if (surface == nullptr)
	{
		std::cout << "Failed to load image. Path: " << path << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Free up the surface now that we have used it to create the texture
	SDL_FreeSurface(surface);
}

Texture::~Texture() 
{
	SDL_DestroyTexture(_data);
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip) 
{
	const int render_success	= 0;
	// Copy a portion of the source texture (clip) to the rendering target (destination)
	int render_result			= SDL_RenderCopyEx(renderer, _data, clip, destination, 0, NULL, flip);
	if (render_result != render_success)
	{
		std::cout << "Failed to render image. " << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

SDL_Texture* Texture::data()
{
	return _data;
}