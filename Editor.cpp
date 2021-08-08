#pragma once

#include "Editor.h"
#include "resource.h"
#include "Player.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

Editor::Editor(std::wstring window_name)
{
	// FindWindow will find a window in the operating system based on a string. 
	// Our window is called "Game" so this will be what it will search for. 
	_window = FindWindow(NULL, window_name.c_str());
	if (_window == NULL)
	{
		std::cout << "Failed to find window. Window Name: " << window_name.c_str() << std::endl;
		exit(1);
	}

	// LoadMenu will load the menu that we created, using an ID. 
	// The default ID will be IDR_MENU1 for the first Menu. 
	_menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	if (_menu == NULL)
	{
		std::cout << "Failed to create menu." << std::endl;
		exit(1);
	}

	BOOL set_menu_result = SetMenu(_window, _menu);
	if (set_menu_result == 0)
	{
		std::cout << "Failed to set menu." << std::endl;
		exit(1);
	}

	// SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE) will allow us to handle events from windows, such as those from our menu's.
	Uint8 event_state_result = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	Uint8 event_state_success = SDL_DISABLE;
	if (event_state_result != event_state_success)
	{
		std::cout << "Failed to enable Windows event state." << std::endl;
		exit(1);
	}
}

Editor::~Editor()
{
}

INT_PTR CALLBACK Dialog_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			EndDialog(hwnd, IDOK);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void Editor::update(Input* input, Scene* scene, Configuration* config)
{
	if (input->is_button_state(Input::Button::DECREASE_SPEED, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player.Walking");
		player->set_speed(player->speed() * 0.9f);
	}

	if (input->is_button_state(Input::Button::INCREASE_SPEED, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player.Walking");
		player->set_speed(player->speed() * 1.1f);
	}

	if (input->is_button_state(Input::Button::SHOW_CREDITS, Input::Button_State::PRESSED))
	{
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), _window, Dialog_Proc);
	}

	if (input->is_button_state(Input::Button::PAUSE, Input::Button_State::PRESSED))
	{
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), _window, Dialog_Proc);
	}

	if (input->is_button_state(Input::Button::DEBUG_SHOW_IDS, Input::Button_State::PRESSED))
	{
		if (config->should_display_ids = !config->should_display_ids == true)
		{
			config->should_display_coordinates = false;
		}
	}

	if (input->is_button_state(Input::Button::DEBUG_SHOW_COORDS, Input::Button_State::PRESSED))
	{
		if (config->should_display_coordinates = !config->should_display_coordinates == true)
		{
			config->should_display_ids = false;
		}
	}

	if (input->is_button_state(Input::Button::PLAYER_NINJA, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player.Walking");
		player->set_texture("Texture.Ninja");
	}

	if (input->is_button_state(Input::Button::PLAYER_ZOMBIE, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player.Walking");
		player->set_texture("Texture.Zombie");
	}
	if (input->is_button_state(Input::Button::PLAYER_KNIGHT, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("Player.Walking");
		player->set_texture("Texture.Player.Walking");
	}
}

