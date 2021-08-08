/*
	Assignment:	Main Assignment: Covid Catcher
	Name:		Stephen Corner
	Student ID:	9014
*/
#include <iostream>
#include <chrono> // used for timing
#include <thread>

#include "engine.h" 
#include "assets.h"
#include "game_scene.h"
#include "input.h"
#include "Editor.h"
#include "configuration.h"

int main(void)
{
	Input*	input			= new Input();
	Configuration* config	= new Configuration();
	Engine* engine			= new Engine("COVID Catcher", config);
	Assets* assets			= new Assets(engine->renderer()); 
	Scene*	game_scene		= new Game_Scene();
	Editor* editor			= new Editor(L"COVID Catcher"); // prefixing with 'L' casts the string as a w_string
	
	const Uint32 milliseconds_per_second	= 1000;
	const Uint32 frames_per_second			= 60;
	const Uint32 frame_time_ms				= milliseconds_per_second / frames_per_second; //16.6667

	Uint32 frame_start_time_ms				= 0;
	Uint32 frame_end_time_ms				= frame_time_ms; // 16.6667
	while (true)
	{
		Uint32 previous_frame_duration	= frame_end_time_ms - frame_start_time_ms; 
		frame_start_time_ms				= SDL_GetTicks();

		input->get_input();
		editor->update(input, game_scene, config);
		engine->simulate(previous_frame_duration, assets, game_scene, input, config);

		if (input->is_button_state(Input::Button::QUIT, Input::Button_State::PRESSED))
		{
			break; // Break from game loop. Will drop to SDL_QUIT and program end.
		}

		
		const Uint32 current_time_ms	= SDL_GetTicks();
		const Uint32 frame_duration_ms	= current_time_ms - frame_start_time_ms;
		/*Perform: as sleep, if the frame duration is less than our desired frame time (in 
		my example it is 16ms, or 1000/60ms) then we want to sleep the thread for the 
		remaining time. e.g. if the frame has taken 2ms we want to sleep for 14ms (16ms - 2ms).*/
		if (frame_duration_ms < frame_time_ms)
		{
			const Uint32 time_to_sleep_for = frame_time_ms - frame_duration_ms;
			std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep_for));
		}

		frame_end_time_ms = SDL_GetTicks();

		//std::cout << frame_end_time_ms - frame_start_time_ms << std::endl;
	}

	SDL_Quit(); // force shutdown of SDL subsystem
	return 0;
}

