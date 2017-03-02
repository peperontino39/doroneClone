#pragma once
#include "Key/Key.h"
#include "Mouse/Mouse.h"

#define c_Input c_InputManager::single()

class c_InputManager
{
public:
	
	bool getKeyPush(const int &);
	bool getKeyPress(const int &);
	bool getKeyPull(const int &);

	bool getMousePush(const int &);
	bool getMousePress(const int &);
	bool getMousePull(const int &);
	ci::Vec2i getMousePos();
	float getWheelIncrement();
	
	static c_InputManager & single() {
		static c_InputManager _input_manager;
		return _input_manager;
	}

private:

};


