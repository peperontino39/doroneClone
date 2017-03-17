#include "MapChipDate.h"
#include "cinder/gl/gl.h"
#include "../../../Utility/Utility/Utility.h"
#include "../../Category/BeltConveyor/ConveyorBase/ConveyorBase.h"
#include "../../Category/BeltConveyor/Conveyor/NomalConveyor.h"

using namespace ci;
using namespace ci::app;

MapChipDate::MapChipDate()
{
	conveyor = new NomalConveyor();

}

void MapChipDate::draw()
{
	gl::pushMatrices();
	gl::multModelView(transform.getMultiMatrix());
	
	conveyor->draw();
	
	gl::popMatrices();
}

void MapChipDate::shutdown()
{
	delete conveyor;
}

ConveyorBase * MapChipDate::getConveyor()
{
	return conveyor;
}

void MapChipDate::setTipe(const ChipTyap & _chip_tyap)
{
	type = _chip_tyap;
	cut_pos =
		ci::Vec2f(
			type % MAPCHIP_TEXTURE_WIDTH,
			type / MAPCHIP_TEXTURE_WIDTH);
	cut_pos /= ci::Vec2f(MAPCHIP_TEXTURE_WIDTH, MAPCHIP_TEXTURE_HEIGHT);

}

void MapChipDate::setSell(const ci::Vec2i & _sell)
{
	sell = _sell;
}

void MapChipDate::setConveyorBase(ConveyorBase * _conveyor)
{
	delete conveyor;
	conveyor = _conveyor;
}

void MapChipDate::setItem(ItemBase * _item)
{
	item = _item;
}

void MapChipDate::changeDirection()
{
	conveyor->changeDirection();
}

void MapChipDate::chipDraw()
{
	gl::pushMatrices();
	gl::multModelView(transform.getMultiMatrix());

	drawQuad(cut_pos, ci::Vec2f(1.f / MAPCHIP_TEXTURE_WIDTH, 1.f / MAPCHIP_TEXTURE_HEIGHT));

	gl::popMatrices();
}
