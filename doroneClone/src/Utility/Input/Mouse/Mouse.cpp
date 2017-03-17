#include "Mouse.h"

bool c_MouseManager::isPush(const int & _botton_num)
{
	return push.find(_botton_num)!= push.end();
}

bool c_MouseManager::isPress(const int & _botton_num)
{
	return press.find(_botton_num) != press.end();
}

bool c_MouseManager::isPull(const int & _botton_num)
{
	return pull.find(_botton_num) != pull.end();
}

ci::Vec2i c_MouseManager::getPos()
{
	return mouse_position;
}

float c_MouseManager::getWheelIncrement()
{
	return wheel_increment;
}

void c_MouseManager::registerDown(ci::app::MouseEvent & _event)
{
	if (_event.isLeft()) {
		push.insert(ci::app::MouseEvent::LEFT_DOWN);
		press.insert(ci::app::MouseEvent::LEFT_DOWN);
	}
	if (_event.isRight()) {
		push.insert(ci::app::MouseEvent::RIGHT_DOWN);
		press.insert(ci::app::MouseEvent::RIGHT_DOWN);
	}
	if (_event.isMiddle()) {
		push.insert(ci::app::MouseEvent::MIDDLE_DOWN);
		press.insert(ci::app::MouseEvent::MIDDLE_DOWN);
	}
}

void c_MouseManager::registerUp(ci::app::MouseEvent & _event)
{
	if (_event.isLeft()) {
		pull.insert(ci::app::MouseEvent::LEFT_DOWN);
		press.erase(ci::app::MouseEvent::LEFT_DOWN);
	}
	if (_event.isRight()) {
		pull.insert(ci::app::MouseEvent::RIGHT_DOWN);
		press.erase(ci::app::MouseEvent::RIGHT_DOWN);
	}
	if (_event.isMiddle()) {
		pull.insert(ci::app::MouseEvent::MIDDLE_DOWN);
		press.erase(ci::app::MouseEvent::MIDDLE_DOWN);
	}
}

void c_MouseManager::registerMove(ci::app::MouseEvent & _event)
{
	mouse_position = _event.getPos();
}

void c_MouseManager::registerDrag(ci::app::MouseEvent & _event)
{
	mouse_position = _event.getPos();
}

void c_MouseManager::registerWheel(ci::app::MouseEvent & _event)
{

	wheel_increment = _event.getWheelIncrement();
}

void c_MouseManager::registerLast()
{
	pull.clear();
	push.clear();
	wheel_increment = 0;
}
