#pragma once

#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"

enum TaskID
{
	STAY,
	MOVE,
	REWIND, //Šª‚«–ß‚è
	REPLAY,
	CLEAR,
	GAMEOVER

};

class CameraWork;
class MyArea;
class Dorone;
class CheckPoint;
class Map;
class DoroneMemory;
class ClearUi;
class MyTimer;

class GameMainTask : public GameObject
{
public:
	GameMainTask();
	
	void setup();


	void update();

	void keyDown();

	void setTaskID(TaskID);

	CameraWork* camera;
	Dorone* dorone;
	CheckPoint* check_point;
	Map* map;
	DoroneMemory* dorone_memory;
	ClearUi* clearui;
	MyTimer* timer;


	bool is_end;
private:
	TaskID task;

};

