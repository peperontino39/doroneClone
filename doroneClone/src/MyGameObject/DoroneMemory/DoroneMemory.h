#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "../../MyGameObject/DroneOneFrame/DroneOneFrame.h"
#include "cinder/gl/Material.h"


class DoroneMemory : public GameObject
{
public:
	DoroneMemory();
	void update();
	void draw();
	
	void pushBack(std::vector<DroneOneFrame>&, ci::gl::Material&);
	void reset();

	bool ishit(ci::Vec3f, float);
	void coundAdd(int);
	int getCount();
	void setCount(int);
	int maxCount();


private:
	struct OneDorone
	{
		std::vector<DroneOneFrame> transfomes;
		ci::gl::Material mat;
		bool ismove = true;
	};
	int count;

	std::vector<OneDorone> memorys;
	TriMeshRef drone;
	TriMeshRef wing;

	int max_count;


};