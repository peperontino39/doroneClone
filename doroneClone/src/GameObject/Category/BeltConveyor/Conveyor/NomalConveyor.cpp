#include "NomalConveyor.h"

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "../../../../Utility/Utility/Utility.h" 
#include "../../../../Utility/AssetManager/TextureManager/TextureManager.h"



using namespace ci;
using namespace ci::app;

NomalConveyor::NomalConveyor()
{
	texture = TextureM.get("Conveyor");
	setDirection(UP);
	transform.position.z+=10;
}

void NomalConveyor::draw()
{
	texture->enableAndBind();
	gl::pushMatrices();
	gl::multModelView(transform.getMultiMatrix());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float time = app::getElapsedSeconds() / 2.f;
	//time = std::fmod(time, 1.f);

	drawQuad(Vec2f(time, 0), Vec2f::one());

	gl::popMatrices();

	texture->disable();
}
