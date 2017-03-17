#include "ItemBase.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "../../../Utility/Utility/Utility.h"

using namespace ci;
using namespace ci::app;

void ItemBase::draw()
{
	
	texture->enableAndBind();

	gl::pushMatrices();
	gl::translate(transform.position);
	gl::multModelView(getLookMatrixY(-Vec3f::zAxis()));
	
	gl::drawSolidRect(Rectf(0.5f, 0.5f, -0.5f, -0.5f));

	gl::popMatrices();

	texture->disable();

}


void ItemBase::setSell(const Vec2i & _sell)
{
	sell = _sell;
}

ci::Vec2i ItemBase::getSell()
{
	return sell;
}


