#pragma once
#include "cinder/app/KeyEvent.h"
#include <set>

#define c_Key c_KeyManager::single() 

class c_KeyManager
{
public:

	bool isPush(const int&);
	bool isPress(const int&);
	bool isPull(const int&);

	void registerDown(ci::app::KeyEvent &);
	void registerUp(ci::app::KeyEvent &);
	void registerLast();

	static c_KeyManager& single() {
		static c_KeyManager _key_manager;
		return _key_manager;
	}
private:
	std::set<int> push;
	std::set<int> press;
	std::set<int> pull;
};


