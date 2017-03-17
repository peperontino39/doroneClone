#include "Map.h"

#include "../MapChipDate/MapChipDate.h"
#include "../../../Utility/AssetManager/TextureManager/TextureManager.h"
#include "../Item/ItemBase.h"
#include "../../../Utility/Easing/Easing.h"
#include "../../../Utility/Coroutine/Coroutine.h"


#include "cinder/Easing.h"
#include "cinder/Ray.h"
#include "cinder/app/App.h"

using namespace ci;
using namespace ci::app;

void Map::setup()
{
	setSize(10, 10);
	map_chip_texture = TextureM.get("mapchip");

}




void Map::mouseMove()
{


}

void Map::mouseDown()
{

}

void Map::shutdown()
{
	for (auto& y : map_chip) {
		for (auto& x : y) {
			x->shutdown();
		}
	}
	dateClear();
}

void Map::draw()
{
}

void Map::nonLightDraw()
{
	gl::color(Color::white());
	map_chip_texture->enableAndBind();
	for (auto& y : map_chip) {
		for (auto& x : y) {

			x->chipDraw();
		}
	}
	map_chip_texture->disable();
	for (auto& y : map_chip) {
		for (auto& x : y) {

			x->draw();
		}
	}

}

ci::Vec2i Map::touchSell(const ci::Ray & _ray)
{
	float t;
	_ray.calcPlaneIntersection(ci::Vec3f::zero(), ci::Vec3f::yAxis(), &t);
	auto pos = _ray.calcPosition(t).xz() + ci::Vec2f::one() * 0.5f;

	return pos;
}

void Map::setSize(const int & _x, const int & _y)
{

	dateClear();
	map_chip = MapChip(_y, std::vector<MapChipDate*>(_x, nullptr));
	for (size_t y = 0; y < map_chip.size(); y++)
	{
		for (size_t x = 0; x < map_chip[y].size(); x++)
		{
			map_chip[y][x] = new MapChipDate();
			map_chip[y][x]->transform.position = ci::Vec3f(x, 0, y);
			map_chip[y][x]->transform.rotate = Quatf(-M_PI / 2, 0, 0);
			map_chip[y][x]->setTipe(ChipTyap::GRASS);
		}
	}
}

void Map::setSize(const ci::Vec2i & _size)
{
	setSize(_size.x, _size.y);
}

void Map::changeConveyorDirection(const ci::Vec2i & _sell)
{
	map_chip[_sell.y][_sell.x]->changeDirection();
}

void Map::onItemMap(ItemBase * _item)
{
	auto _sell = _item->getSell();
	_sell += map_chip[_sell.y][_sell.x]->
	map_chip[_sell.y][_sell.x]->setItem(_item);


	Easing<Vec3f>::apply(_item->transform.position,
		map_chip[_sell.y][_sell.x]->transform.position,
		EaseNone(), 1.f);

	c_Coroutine(1, [_item,this]() {
		_item->setSell(Vec2i(1, 0));
		auto _sell = _item->getSell();

		Easing<Vec3f>::apply(_item->transform.position,
			map_chip[_sell.y][_sell.x]->transform.position,
			EaseNone(), 1.f);

	});

	
}


bool Map::isOutRange(const ci::Vec2i& _sell)
{


}





void Map::dateClear()
{
	for (auto& y : map_chip) {
		for (auto& x : y) {
			delete x;
		}
	}
	map_chip.clear();
}


