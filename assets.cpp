#include "assets.h"

// Purpose: Creates new Assets and puts the pointer to it in a string-indexed array "_assets"
Assets::Assets(SDL_Renderer* renderer)
{


	// Syringe
	{
		Texture* texture = new Texture("Texture.Syringe", "Assets/Syringe (green).png", renderer);
		_assets[texture->id()] = texture; // Map the ID of this texture to its pointer
	}
	// Handcuffs
	{
		Texture* texture = new Texture("Texture.Handcuffs", "Assets/handcuffs.png", renderer);
		_assets[texture->id()] = texture; // Map the ID of this texture to its pointer
	}

	// Title
	{
		Texture* texture = new Texture("Texture.Title", "Assets/title1.png", renderer);
		_assets[texture->id()] = texture; // Map the ID of this texture to its pointer
	}

	// Animated Dino
	{
		int frame_count = 10;
		Uint32 frame_duration_milliseconds = 200;
		Animated_Texture* texture = new Animated_Texture("Texture.Dino.Walking", "Assets/dino.walking.png", renderer, frame_count,
			frame_duration_milliseconds);
		_assets[texture->id()] = texture; // Map the ID of this texture to its pointer
	}
	
	 //Animated Zombie Girl
	{
		int frame_count = 10;
		Uint32 frame_duration_milliseconds = 100;
		Texture* texture = new Animated_Texture("Texture.Zombie", "Assets/zombie.png", renderer, frame_count,
			frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	//Animated Ninja
	{
		int frame_count = 10;
		Uint32 frame_duration_milliseconds = 100;
		Texture* texture = new Animated_Texture("Texture.Ninja", "Assets/ninja.png", renderer, frame_count,
			frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}
	
	// Animated Walking Player
	{
		int frame_count = 10;
		Uint32 frame_duration_milliseconds = 100;
		Texture* texture = new Animated_Texture("Texture.Player.Walking", "Assets/player.walking.png", renderer, frame_count,
			frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Animated Running Player
	{
		int frame_count = 10;
		Uint32 frame_duration_milliseconds = 100;
		Texture* texture = new Animated_Texture("Texture.Player.Running", "Assets/player.running.png", renderer, frame_count,
			frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Animated Idle Player
	{
		int frame_count = 10;
		Uint32 frame_duration_milliseconds = 100;
		Texture* texture = new Animated_Texture("Texture.Player.Idle", "Assets/player.idle.png", renderer, frame_count,
			frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}
	
	// Collider - create collider texture
	{
		Texture* texture = new Texture("Texture.Collider", "Assets/collider.png", renderer);
		_assets[texture->id()] = texture; // Map the ID of this texture to its pointer
	}

	// Create music sound
	{
		Sound* sound = new Sound("Sound.Music", "Assets/music.wav");
		_assets[sound->id()] = sound;

		Mix_PlayChannel(0, sound->data(), -1);
	}

	// Create running sound
	{
		Sound* sound = new Sound("Sound.Running", "Assets/running.wav");
		_assets[sound->id()] = sound;
	}

	// Create walking sound
	{
		Sound* sound = new Sound("Sound.Walking", "Assets/walking.wav");
		_assets[sound->id()] = sound;
	}

	// Animated Portal Entry
	{
		int frame_count = 8;
		Uint32 frame_duration_milliseconds = 100;
		Asset* animated_texture = new Animated_Texture("Texture.Portal.Entry", "Assets/portal.green.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[animated_texture->id()] = animated_texture;
	}

	// Animated Portal Exit
	{
		const int frame_count = 8;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* animated_texture = new Animated_Texture("Texture.Portal.Exit", "Assets/portal.purple.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[animated_texture->id()] = animated_texture;
	}
}

Assets::~Assets() {
	// delete map
	_assets.clear();
}

// get_asset(id) provides assets from the map.
Asset* Assets::get_asset(std::string id)
{
	// retrieve the texture from the map using the provided id string
	if (_assets.find(id) == _assets.end())
	{
		std::cout << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit(1);
	}
	return _assets[id];
}

