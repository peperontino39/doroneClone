#include "Timer.h"
#include "cinder/gl/gl.h"
//#include ""
using namespace ci;
using namespace ci::app;

void Timer::setup()
{
	font = Font("Hiragino Maru Gothic ProN W4", 60.0f);
	is_countdown = false;
}

void Timer::drawUI()
{

	gl::pushModelView();
	gl::translate(0, -250);
	gl::scale(2, 2);
	gl::drawStringCentered(u8"" + std::to_string((int)((float)timer / 60.f)), Vec2f::zero(), Color::white(), font);
	gl::popModelView();
}

void Timer::update()
{
	if (is_countdown) {
		timer--;
		timer = std::max(timer, 0);
	}
}

bool Timer::isCountEnd()
{
	return timer == 0;
}
