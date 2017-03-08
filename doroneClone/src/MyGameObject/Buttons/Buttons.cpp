#include "Buttons.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"
#include "../../System/Input/Input.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/Rect.h"

using namespace ci;
using namespace ci::app;

Buttons::Buttons()
{
	size = Vec2i::one() * 90;
	int one_retu = 10;
	for (int i = 0; i < 30; i++)
	{
		poss.push_back(
			size * Vec2i(i % one_retu, i / one_retu) 
			- Vec2i(size.x * (one_retu - 1) / 2, 0));

	}
	font = Font("Hiragino Maru Gothic ProN W4", 60.0f);

	stage_num = -1;
	is_ok = false;
}

void Buttons::drawUI()
{
	gl::pushModelView();

	gl::scale(3, 3);
	gl::drawStringCentered(u8"DRONE CLONE",
		Vec2i(0,getWindowHeight()/-2+200),
		Color::white(), font);

	gl::popModelView();

	for (size_t i = 0; i < poss.size(); i++)
	{
		
		gl::pushModelView();
		gl::translate(poss[i].x, poss[i].y);

		gl::drawStrokedRect(ci::Rectf(-size.x / 2, -size.y / 2, size.x / 2, size.y / 2));
		gl::drawStringCentered(u8"" + std::to_string(i + 1), Vec2f::zero(), Color::white(), font);
		gl::popModelView();
	}

}

bool ishitRectToPoint(Vec2i _point, Vec2i _pos, Vec2i size) {
	if (_pos.x - size.x / 2 < _point.x && _point.x < _pos.x + size.x / 2)
		if (_pos.y - size.y / 2 < _point.y && _point.y < _pos.y + size.y / 2)
			return true;
	return false;

}

void Buttons::update()
{
	if(c_Input.getMousePush(MouseEvent::LEFT_DOWN)){
		auto mpos = c_Input.getMousePos() - getWindowSize() / 2;

		for (size_t i = 0; i < poss.size(); i++)
		{
			if (ishitRectToPoint(mpos, poss[i], size)) {
				stage_num = i + 1;
				is_ok = true;
			}
		}
	}
	
	//console() << stage_num << std::endl;
}

bool Buttons::isOk()
{
	//console() << stage_num << std::endl;
	//if(c_Input.getMousePush(MouseEvent::LEFT_DOWN))
	return is_ok;
	return false;

}

int Buttons::getStageNum()
{
	return stage_num;
}
