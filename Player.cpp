#pragma once

#include "Player.h"
#include "Sound.h"

Player::Player(std::string id)
	: Game_Object(id, "Texture.Player.Walking")
{
	_speed = 0.1f;

	// Set the translation to the feet of the Game Object
	// and make the radius smaller than the actual Game Object.
	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::IDLE);
}
Player::~Player()
{
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

// Use Input to determine if buttons are pressed and change the position of the Game Object accordingly
void Player::simulate_AI(Uint32 , Assets* assets, Input* input, Scene*)
{
	// Logic for when pushing and popping state.
	switch (_state.top())
	{
	case State::IDLE:
		if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::DOWN) && _velocity.magnitude() > 0.0f)
		// if Player is moving and left-shift is down: start running
		{
			push_state(State::RUNNING, assets);
		}
		else if (_velocity.magnitude() > 0.0f)
		// if Player is moving and left-shift is not down: start walking
		{
			push_state(State::WALKING, assets);
		}
		break;
	case State::WALKING:
		if (_velocity.magnitude() == 0.0f)
		// stop walking if player stops moving
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::PRESSED))
		// if walking and left-shift pressed: start running
		{
			push_state(State::RUNNING, assets);
		}
		break;
	case State::RUNNING:
		if (_velocity.magnitude() == 0.0f)
		// stop running if Player stops moving
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::RELEASED))
		// stop running when left-shift button released
		{
			pop_state(assets);
		}
		break;
	}

	_velocity = Vector_2D(0, 0);

	/*
	Remember from the Timing tutorial that we should use milliseconds_to_simulate to make sure that our 
	objects are reacting to how much time the engine should simulate.
	If we did _x += 1; here and we were running at 30fps, one second would equate to 30 units of movement.
	If we did _x += 1; here and we were running at 50fps, one second would equate to 50 units of movement.
	We want our players to move the same distance regardless of the fps. That's why we used 
	milliseconds_to_simulate which will be 1 unit per second at any fps.
	*/
	if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(1.0f, 0);
	}
	if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(-1.0f, 0);
	}
	if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, -1.0f);
	}
	if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, 1.0f);
	}

	_velocity.normalise();
	_velocity.scale(_speed);
}

//push and pop states. This will make sure each state has a chance to execute exit logic and entry logic.
void Player::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}
void Player::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player::handle_enter_state(State state, Assets* assets)
{
	switch (state)
	{
		case State::IDLE:
			_texture_id = "Texture.Player.Idle";
			break;
		case State::WALKING:
		{
			_texture_id = "Texture.Player.Walking";
			_speed = 0.15f;
			const int walking_channel = 1;
			Sound* sound = (Sound*)assets->get_asset("Sound.Walking");
			Mix_PlayChannel(walking_channel, sound->data(), -1);
			break;
		}
		case State::RUNNING:
		{
			_texture_id = "Texture.Player.Running";
			_speed = 0.3f;
			const int running_channel = 2;
			Sound* sound = (Sound*)assets->get_asset("Sound.Running");
			Mix_PlayChannel(running_channel, sound->data(), -1);
			break;
		}
	}
}

void Player::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
		case State::IDLE:
			break;
		case State::WALKING:
		{
			const int walking_channel = 1;
			Mix_HaltChannel(walking_channel);
			break;
		}
		case State::RUNNING:
		{
			const int running_channel = 2;
			Mix_HaltChannel(running_channel);
			break;
		}
	}
}

void Player::set_speed(float speed)
{
	_speed = speed;
}

float Player::speed()
{
	return _speed;
}