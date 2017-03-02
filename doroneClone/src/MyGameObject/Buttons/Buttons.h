#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/Vector.h"
#include "cinder/Font.h"

class Buttons : public GameObject
{
public:
	Buttons();

	void drawUI();
	void update();
	bool isOk();
	int getStageNum();



private:
	std::vector<ci::Vec2f> poss;
	ci::Vec2i size;
	ci::Font font;
	ci::gl::TextureRef bg;

	int stage_num;
	bool is_ok;
};

