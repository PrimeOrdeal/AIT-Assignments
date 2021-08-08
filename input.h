#pragma once

#include <map>

class Input
{
public:
	Input();
	~Input();

	enum class Button
	{
		QUIT,

		UP,
		DOWN,
		LEFT,
		RIGHT,

		INCREASE_SPEED,
		DECREASE_SPEED,

		SHOW_CREDITS,
		PAUSE,

		DEBUG_SHOW_COORDS,
		DEBUG_SHOW_IDS,

		PLAYER_KNIGHT,
		PLAYER_NINJA,
		PLAYER_ZOMBIE,

		RUNNING,
		WALKING,
		IDLE
	};

	enum class Button_State
	{
		PRESSED,
		DOWN,
		RELEASED,
		UP
	};

	void get_input(); // SHould be called once per frame
	bool is_button_state(Button type, Button_State state); // Used to check the state of the button

private:
	std::map<Button, Button_State> _button_state;
};

