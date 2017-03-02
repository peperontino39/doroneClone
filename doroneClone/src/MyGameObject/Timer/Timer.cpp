#include "Timer.h"
#include "cinder/gl/gl.h"
//#include ""
using namespace ci;
using namespace ci::app;

void MyTimer::setup()
{
	font = Font("Hiragino Maru Gothic ProN W4", 60.0f);
	is_countdown = false;
}

void MyTimer::drawUI()
{

	gl::pushModelView();
	gl::translate(0, -250);
	gl::scale(2, 2);
	gl::drawStringCentered(u8"" + std::to_string((int)((float)timer / 60.f)), Vec2f::zero(), Color::white(), font);
	gl::popModelView();
}

void MyTimer::update()
{
	if (is_countdown) {
		timer--;
		timer = std::max(timer, 0);
	}
}

bool MyTimer::isCountEnd()
{
	return timer == 0;
}
