#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"


class MyArea : public GameObject
{
public:
	MyArea();
	void update();
	void draw();

	void setObjectPtr(GameObject*);

	void setMyArea(ci::Vec3f, ci::Vec3f);


private:
	std::vector<GameObject*> gameobjects;
};




