#pragma once
#include "../../System/CinderFwd.h"
#include "../../Transform/Transform.h"
#include "../../GameObject/GameObject.h"
#include <list>

class MyArea;
class Dorone;
class CheckPoint;
class CameraWork;

class Map : public GameObject
{
public:
	Map(int);

	void setup();
	void update();
	void draw();

	bool istrigr();

	Dorone* onDorones;
	std::function<void()> onGroundFn;

	MyArea * my_area;
	CheckPoint* check_point;
	CameraWork* camera;
	bool isHitTriMeshToSphere();

private:
	struct ObstacleDate
	{
		Transform transform;
		TriMeshRef mesh;
		MaterialRef material;
		ci::gl::TextureRef texture;
	};
	std::list<ObstacleDate> obstacles;
	std::list<ObstacleDate> grounds;

	int stage_num;
};

