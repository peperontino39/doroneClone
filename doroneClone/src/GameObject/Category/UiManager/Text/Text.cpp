#include "Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"

void Text::drawUI()
{
	ci::gl::pushMatrices();
	ci::gl::draw(ci::gl::Texture(textbox.render()));


	ci::gl::popMatrices();

}
