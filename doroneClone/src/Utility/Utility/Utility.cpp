#include "Utility.h"
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/Json.h"
#include "cinder/Matrix44.h" 

using namespace ci;
using namespace ci::app;


void drawGrid(float size, float step)
{
	for (float i = -size; i <= size; i += step) {
		ci::gl::drawLine(ci::Vec3f(i, 0.0f, -size), ci::Vec3f(i, 0.0f, size));
		ci::gl::drawLine(ci::Vec3f(-size, 0.0f, i), ci::Vec3f(size, 0.0f, i));
	}


}

std::string FileName(const std::string & _path)
{
	return _path.substr(_path.rfind("\\") + 1, _path.length());
}


std::string NonExtensionFileName(const std::string& _path)
{
	return _path.substr(0, _path.rfind("."));
}

ci::Vec3f JtoVec3f(ci::JsonTree & _json)
{
	return ci::Vec3f(
		_json.getValueAtIndex<float>(0),
		_json.getValueAtIndex<float>(1),
		_json.getValueAtIndex<float>(2));
}

ci::Matrix44f getLookMatrix(const ci::Vec3f & vec = -ci::Vec3f::zAxis())
{
	return
		Matrix44f::createRotation(Vec3f::zAxis(), gl::getModelView().inverted().transformVec(vec), Vec3f::yAxis());
}

ci::Matrix44f getLookMatrixY(const ci::Vec3f & vec = -ci::Vec3f::zAxis())
{
	Vec3f rot_vec = gl::getModelView().inverted().transformVec(vec);
	rot_vec.y = 0;
	return
		Matrix44f::createRotation(Vec3f::zAxis(), rot_vec, Vec3f::yAxis());
}

void drawQuad(const ci::Vec2f & _cut_pos, const ci::Vec2f & _cut_size)
{
	
	gl::begin(GL_QUADS);
	gl::texCoord(_cut_pos.x, _cut_pos.y);    gl::vertex(-.5, .5);
	gl::texCoord(_cut_pos.x, _cut_pos.y + _cut_size.y);    gl::vertex(-.5, -.5);
	gl::texCoord(_cut_pos.x + _cut_size.x, _cut_pos.y + _cut_size.y);    gl::vertex(.5, -.5);
	gl::texCoord(_cut_pos.x + _cut_size.x, _cut_pos.y);    gl::vertex(.5, .5);
	gl::end();

}
