#include "Input.h"

bool c_InputManager::getKeyPush(const int & _key_num)
{
	return c_Key.isPush(_key_num);
}

bool c_InputManager::getKeyPress(const int & _key_num)
{
	return c_Key.isPress(_key_num);
}

bool c_InputManager::getKeyPull(const int & _key_num)
{
	return c_Key.isPull(_key_num);
}

bool c_InputManager::getMousePush(const int & _botton_num)
{
	return c_Mouse.isPush(_botton_num);
}

bool c_InputManager::getMousePress(const int & _botton_num)
{
	return c_Mouse.isPress(_botton_num);
}

bool c_InputManager::getMousePull(const int & _botton_num)
{
	return c_Mouse.isPull(_botton_num);
}

ci::Vec2i c_InputManager::getMousePos()
{
	return c_Mouse.getPos();
}

float c_InputManager::getWheelIncrement()
{
	return c_Mouse.getWheelIncrement();
}
