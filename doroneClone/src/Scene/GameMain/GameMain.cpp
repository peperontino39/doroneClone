#include "GameMain.h"
#include "../../MyGameObject/MyEditCamera/MyEditCamera.h"
#include "../../Scene/StageCreate/StageCreate.h"
#include "../../System/Input/Input.h"
#include "../../MyGameObject/Dorone/Dorone.h"
#include "../../MyGameObject/MyArea/MyArea.h" 
#include "../../MyGameObject/MyLight/MyLight.h" 
#include "../../MyGameObject/Map/Map.h"
#include "../../MyGameObject/CameraWork/CameraWork.h"
#include "../../MyGameObject/DoroneMemory/DoroneMemory.h"
#include "../../MyGameObject/CheckPoint/CheckPoint.h"
#include "../../MyGameObject/GameMainTask/GameMainTaskh.h"
#include "../../MyGameObject/Skydome/Skydome.h"
#include "../../MyGameObject/ClearUi/ClearUi.h"
#include "../../MyGameObject/Timer/Timer.h"
#include "../../Scene/StageSelect/StageSelect.h"


GameMain::GameMain(int _stage)
{
	stage_num = _stage;
}

void GameMain::onCreate()
{
	//MyEditCamera* camera = Instantiate(new MyEditCamera());
	Map* map = Instantiate(new Map(stage_num));
	Dorone* dorone = Instantiate(new Dorone());
	MyArea * myarea = Instantiate(new MyArea());
	MyLight* myLight = Instantiate(new MyLight());
	CameraWork* camera = Instantiate(new CameraWork());
	DoroneMemory* dorone_memory = Instantiate(new DoroneMemory());
	CheckPoint* check_point = Instantiate(new CheckPoint());
	GameMainTask* gamemaintask = Instantiate(new GameMainTask());
	ClearUi* clearUi = Instantiate(new ClearUi());
	Timer* timer = Instantiate(new Timer());

	Instantiate(new Skydome());

	check_point->dorone = dorone;
	check_point->map = map;

	map->check_point = check_point;
	map->my_area = myarea;
	map->onDorones = dorone;
	map->onGroundFn = std::bind(&Dorone::onGround, dorone);
	map->camera = camera;

	myarea->setObjectPtr(dorone);

	dorone->camera = camera;
	dorone->dorone_memory = dorone_memory;

	gamemaintask->camera = camera;
	gamemaintask->dorone = dorone;
	gamemaintask->check_point = check_point;
	gamemaintask->map = map;
	gamemaintask->dorone_memory = dorone_memory;
	gamemaintask->clearui = clearUi;
	gamemaintask->timer = timer;

	is_end = &gamemaintask->is_end;

	nextScene = [&] {
		SceneBase*  next = nullptr;
		if (map->istrigr()) {
			next = new StageCreate();
		}
		if (*is_end) {
			next = new StageSelect();
		}
		return next;
	};

}
