#include "GameMainTaskh.h"
#include "../../MyGameObject/CameraWork/CameraWork.h"
#include "../../MyGameObject/Dorone/Dorone.h"
#include "cinder/Vector.h"
#include "../../System/Input/Input.h"
#include "../../MyGameObject/CheckPoint/CheckPoint.h"
#include "../../MyGameObject/Map/Map.h"
#include "../../MyGameObject/DoroneMemory/DoroneMemory.h"
#include "../../MyGameObject/ClearUi/ClearUi.h"
#include "../../MyGameObject/Timer/Timer.h"

#include "../../AssetManager/SoundManager/SoundManager.h"


using namespace ci;
using namespace ci::app;

GameMainTask::GameMainTask()
{

}

void GameMainTask::setup()
{
	setTaskID(TaskID::STAY);
	is_end = false;
}

void GameMainTask::update()
{

	switch (task)
	{
	case STAY:
		break;
	case MOVE:
		dorone_memory->coundAdd(1);
		camera->setTransfome(dorone->transform);
		if (dorone_memory->ishit(dorone->transform.position, dorone->getRadius() + dorone->getRadius()))
		{
			setTaskID(TaskID::REWIND);
			Sounds.get("dame")->start();

		}
		if (map->isHitTriMeshToSphere()) {
			setTaskID(TaskID::REWIND);
			Sounds.get("dame")->start();

		}
		if (check_point->isGoal()) {
			check_point->goalFn();
			dorone->onGoal();
			Sounds.get("se")->start();

			if (check_point->isAllClear()) {
				setTaskID(TaskID::REPLAY);
				dorone->setIsDraw(false);
				break;
			}
			setTaskID(TaskID::STAY);
		}
		if (timer->isCountEnd()) {
			setTaskID(TaskID::GAMEOVER);
		}

		break;
	case REWIND:
		dorone_memory->coundAdd(-3);
		dorone->setMemoryTransform(dorone_memory->getCount());
		if (dorone_memory->getCount() == 0) {
			dorone->memoryClear();
			setTaskID(TaskID::STAY);
		}


		break;

	case REPLAY:
		dorone_memory->coundAdd(1);

		if (dorone_memory->getCount() == dorone_memory->maxCount() || 
			c_Input.getKeyPush(KeyEvent::KEY_RETURN)) {
			
			if (check_point->isAllClear()) {
				setTaskID(TaskID::CLEAR);
			}
			else {
				setTaskID(TaskID::GAMEOVER);
			}

		}
		break;
	case CLEAR:
		dorone_memory->coundAdd(1);

		if (c_Input.getKeyPush(KeyEvent::KEY_RETURN)) {

			is_end = true;

		}
		break;
	case GAMEOVER:
		if (c_Input.getKeyPush(KeyEvent::KEY_RETURN)) {

			is_end = true;

		}

		break;
	default:
		break;
	}
}

void GameMainTask::setTaskID(TaskID _id)
{
	task = _id;
	float _time = 2;
	timer->is_countdown = false;
	switch (task)
	{
	case STAY:
		camera->setCenterE(ci::Vec3f::zero(), _time);
		camera->setDirectionE(ci::Vec3f::yAxis() * Quatf(45, 0, 0), _time);
		camera->setLengthE(100, _time);
		dorone_memory->setCount(0);

		break;
	case MOVE:
		camera->setLengthE(20, _time);
		camera->setTransfomeE(dorone->transform, _time);
		dorone->setIsMove(true);

		timer->is_countdown = true;

		break;
	case REWIND:
		camera->setCenterE(ci::Vec3f::zero(), _time);
		camera->setDirectionE(ci::Vec3f::yAxis() * Quatf(45, 0, 0), _time);
		camera->setLengthE(100, _time);

		dorone->setIsMove(false);

		dorone->hitFn();
		break;
	case REPLAY:
		camera->setCenterE(ci::Vec3f::zero(), _time);
		camera->setDirectionE(ci::Vec3f::yAxis() * Quatf(45, 0, 0), _time);
		camera->setLengthE(100, _time);

		dorone->setIsMove(false);

		dorone_memory->setCount(0);

		break;
	case CLEAR:
		camera->setCenterE(ci::Vec3f::zero(), _time);
		camera->setDirectionE(ci::Vec3f::yAxis() * Quatf(45, 0, 0), _time);
		camera->setLengthE(100, _time);
		clearui->mes = "CLEAR";
		clearui->easeStart();
		break;
	case GAMEOVER:
		camera->setCenterE(ci::Vec3f::zero(), _time);
		camera->setDirectionE(ci::Vec3f::yAxis() * Quatf(45, 0, 0), _time);
		camera->setLengthE(100, _time);
		clearui->mes = "GAMEOVER";
		clearui->easeStart();
		break;

	default:
		break;
	}
}

void GameMainTask::keyDown()
{
	if (c_Input.getKeyPush(KeyEvent::KEY_RETURN)) {
		if (task == TaskID::STAY) {
			setTaskID(TaskID::MOVE);

		}
	}
}
