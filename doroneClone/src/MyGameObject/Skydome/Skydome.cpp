#include "Skydome.h"
#include "../../AssetManager/TextureManager/TextureManager.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

void Skydome::setup()
{
	texture = Textures.get("default");
	transform.scale = ci::Vec3f::one() * 500;


}

void Skydome::draw()
{
	glCullFace(GL_FRONT);
	gl::disable(GL_LIGHTING);
	gl::disable(GL_NORMALIZE);

	gl::pushMatrices();
	gl::multModelView(transform.getMultiMatrix());
	texture->enableAndBind();
	gl::drawSphere(Vec3f::zero(), 1);
	texture->disable();


	gl::popMatrices();



		glCullFace(GL_BACK);
	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);
}
