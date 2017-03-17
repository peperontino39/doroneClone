#pragma once
#include "../../GameObject.h"


class ItemBase : public GameObject
{
public:

	void draw()override;

	void setSell(const ci::Vec2i&);
	ci::Vec2i getSell();


protected:

	ci::Vec2i sell;
	ci::gl::TextureRef texture;

};



