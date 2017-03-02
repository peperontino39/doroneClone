#include "MyArea.h"
#include <algorithm>
#include "cinder/gl/gl.h"
#include "../../System/Interface/Interface.h"
#include "cinder/params/Params.h"

MyArea::MyArea()
{
	/*c_Interface.create();
	c_Interface.get()->addParam("pos", &transform.position);
	c_Interface.get()->addParam("scl", &transform.scale);
	c_Interface.get()->addParam("rot", &transform.rotate);
	transform.scale = ci::Vec3f::one() * 200;*/
}

void MyArea::update()
{
	for (auto& obj : gameobjects)
	{
		obj->transform.position.x =
			std::min(std::max(obj->transform.position.x,
				transform.position.x - transform.scale.x / 2),
				transform.position.x + transform.scale.x / 2);
		obj->transform.position.y =
			std::min(std::max(obj->transform.position.y,
				transform.position.y - transform.scale.y / 2),
				transform.position.y + transform.scale.y / 2);
		obj->transform.position.z =
			std::min(std::max(obj->transform.position.z,
				transform.position.z - transform.scale.z / 2),
				transform.position.z + transform.scale.z / 2);
	}
}

void MyArea::draw()
{
	
	ci::gl::drawStrokedCube(transform.position, transform.scale);

}

void MyArea::setObjectPtr(GameObject * obj)
{
	gameobjects.push_back(obj);

}

void MyArea::setMyArea(ci::Vec3f _pos, ci::Vec3f _scale)
{
	transform.position = _pos;
	transform.scale = _scale;


}
