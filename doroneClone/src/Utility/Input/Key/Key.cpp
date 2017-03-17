#include "Key.h"


bool c_KeyManager::isPush(const int & _key_num)
{
	return push.find(_key_num) != push.end();
}

bool c_KeyManager::isPress(const int & _key_num)
{
	return press.find(_key_num) != press.end();
}

bool c_KeyManager::isPull(const int & _key_num)
{
	return pull.find(_key_num) != pull.end();
}

void c_KeyManager::registerDown(ci::app::KeyEvent & _event)
{
	if (press.find(_event.getCode()) == press.end()) {
		push.insert(_event.getCode());
	}
	press.insert(_event.getCode());
}

void c_KeyManager::registerUp(ci::app::KeyEvent & _event)
{
	press.erase(_event.getCode());
	pull.insert(_event.getCode());
}

void c_KeyManager::registerLast()
{
	push.clear();
	pull.clear();
}
