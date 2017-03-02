#pragma once
#include "cinder/app/MouseEvent.h"
#include <set>

#define c_Mouse c_MouseManager::single() 


class c_MouseManager
{
public:
	
	bool isPush(const int&);
	bool isPress(const int&);
	bool isPull(const int&);
	ci::Vec2i getPos();
	float getWheelIncrement();


	void registerDown(ci::app::MouseEvent &);
	void registerUp(ci::app::MouseEvent &);
	void registerMove(ci::app::MouseEvent &);
	void registerDrag(ci::app::MouseEvent &);
	void registerWheel(ci::app::MouseEvent &);
	void registerLast();

	static c_MouseManager & single() {
		static c_MouseManager _mouse_manager;
		return _mouse_manager;
	}


private:
	std::set<int> push;
	std::set<int> press;
	std::set<int> pull;


	ci::Vec2i mouse_position;
	float wheel_increment;

};

