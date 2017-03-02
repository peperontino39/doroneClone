#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/Vector.h"

class MyLight : public GameObject
{
public:
	MyLight();
	~MyLight();
	void lightDrawBegin();
	void lightDrawEnd();

private:
	ci::gl::Light* light;
	ci::Vec3f direction;
};

