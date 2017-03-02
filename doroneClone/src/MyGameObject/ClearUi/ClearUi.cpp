#include "ClearUi.h"
#include "cinder/gl/gl.h"
#include "../../System/Easing/Easing.h"
#include "cinder/Easing.h"


using namespace ci;
using namespace ci::app;

void ClearUi::setup()
{
	font = Font("Hiragino Maru Gothic ProN W4", 60.0f);
	size = 0;
	mes = "CLEAR";
	mes = "GAMEOVER";

}

void ClearUi::drawUI()
{
	gl::pushModelView();
	//gl::translate(poss[i].x, poss[i].y);
	gl::scale(size, size);
	//gl::drawStrokedRect(ci::Rectf(-size.x / 2, -size.y / 2, size.x / 2, size.y / 2));
	gl::drawStringCentered(u8"" + mes, Vec2f::zero(), Color::white(), font);
	gl::popModelView();

}

void ClearUi::easeStart()
{
	Easing<float>::apply(size, 3.f, EaseOutCubic(), 1);
}
