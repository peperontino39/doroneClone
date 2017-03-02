#include "Utility.h"
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/Json.h"

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
