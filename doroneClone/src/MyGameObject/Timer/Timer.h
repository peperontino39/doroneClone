#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/Font.h"

class Timer : public GameObject
{
public:

	void setup();
	void drawUI();
	void update();

	bool isCountEnd();


	bool is_countdown;
private:
	ci::Font font;
	int timer = 60 * 60;
};
