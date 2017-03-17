#include "MapItem.h"
#include "cinder/gl/gl.h"

#include "../Item/ItemBase.h"
#include "../Item/Wood/Wood.h"

using namespace ci;
using namespace ci::app;

void MapItem::setup()
{
	
	//instans(new Wood());
}

void MapItem::nonLightDraw()
{
	ci::gl::color(ci::Color::white());
	for (auto& ite : items) {
		ite->draw();
	}
}



void MapItem::shutdown()
{
	for (auto& ite : items) {
		delete ite;
	}
}

void MapItem::instans(ItemBase * _item)
{
	items.push_back(_item);
}

void MapItem::nullCheck()
{
	for (auto it = items.begin();
	it != items.end(); )
	{
		if (*(it) == nullptr) {
			it = items.erase(it);

			continue;
		}
		it++;
	}
}
