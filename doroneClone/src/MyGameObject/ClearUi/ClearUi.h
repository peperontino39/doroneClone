#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/Font.h"
#include "cinder/Easing.h"

using namespace ci;
using namespace ci::app;

class ClearUi : public GameObject
{
public:


	void setup();

	void drawUI();
	void easeStart();

	std::string mes;
private:
	ci::Font font;
	float size;
};
