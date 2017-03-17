#pragma once
#include "../ConveyorBase/ConveyorBase.h"


class NomalConveyor : public ConveyorBase
{
public:
	NomalConveyor();
	void draw()override;

private:

	ci::gl::TextureRef texture;

};
