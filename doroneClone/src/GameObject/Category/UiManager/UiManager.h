#pragma once
#include "../../GameObject.h"
#include <map>

class UiBase;

class UiManager : public GameObject
{
	void drawUI()override;


public:

	std::map<std::string, UiBase*> uis;
};