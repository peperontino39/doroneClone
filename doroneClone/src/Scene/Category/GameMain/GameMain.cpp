#include "GameMain.h"


#include "../../../GameObject/Category/MyEditCamera/MyEditCamera.h"
#include "../../../GameObject/Category/BeltConveyor/BeltConveyor.h"
#include "../../../GameObject/Category/Map/Map.h"
#include "../../../GameObject/Category/GameMainTask/GameMainTask.h"
#include "../../../GameObject/Category/MapItem/MapItem.h"



void GameMain::onCreate()
{
	auto camera = Instantiate(new MyEditCamera());
	auto map = Instantiate(new Map());
	auto map_item = Instantiate(new MapItem());

	auto game_main_task = Instantiate(new GameMainTask());


	game_main_task->camera = camera;
	game_main_task->map = map;
	game_main_task->map_item = map_item;

}
