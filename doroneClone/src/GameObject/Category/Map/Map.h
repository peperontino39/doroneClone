#pragma once
#include "../../GameObject.h"

class MapChipDate;
class ItemBase;
typedef std::vector<std::vector<MapChipDate*>> MapChip;

class Map : public GameObject
{
public:

	void setup()override;
	void mouseMove()override;
	void mouseDown()override;
	void shutdown() override;
	void draw() override;
	void nonLightDraw()override;


	ci::Vec2i touchSell(const ci::Ray&);
	void setSize(const int&, const int&);
	void setSize(const ci::Vec2i &);
	void changeConveyorDirection(const ci::Vec2i &);
	void onItemMap(ItemBase*);
	bool isOutRange(const ci::Vec2i&);



private:
	void dateClear();


	MapChip map_chip;
	ci::Vec2i size;
	ci::gl::TextureRef map_chip_texture;

};