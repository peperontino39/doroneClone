#include "GameMainTask.h"
#include "cinder/Ray.h"

#include "../../../Utility/Input/Input.h"

#include "../BeltConveyor/BeltConveyor.h"
#include "../Map/Map.h"
#include "../MyEditCamera/MyEditCamera.h"
#include "../MapItem/MapItem.h"
#include "../Item/ItemBase.h"

#include "../Item/Wood/Wood.h"

using namespace ci;
using namespace ci::app;

void GameMainTask::setup()
{
	
	test = new Wood();
	test->setSell(Vec2i::zero());
	map_item->instans(test);

}

void GameMainTask::update()
{

}

void GameMainTask::draw()
{
}

void GameMainTask::mouseDown()
{

	if (c_Input.getMousePush(MouseEvent::LEFT_DOWN)) {

		auto _sell = map->touchSell(camera->getRay());
		map->changeConveyorDirection(_sell);
	
	}

}

void GameMainTask::mouseMove()
{
	
}

void GameMainTask::keyDown()
{
	if (c_Input.getKeyPush(KeyEvent::KEY_0)) {
		createItem(test);
	}
}

void GameMainTask::createItem(ItemBase * _item)
{
	
	map->onItemMap(_item);
}
