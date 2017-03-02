#pragma once
#include "../../GameObject/GameObject.h"


class Skydome : public GameObject
{
public:
	void setup();

	void draw();

private:
	

	ci::gl::TextureRef texture;

};

