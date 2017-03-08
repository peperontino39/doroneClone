#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/Vector.h"
#include "../../MyGameObject/DroneOneFrame/DroneOneFrame.h"
#include <list>

class CameraWork;
class DoroneMemory;

class Dorone : public GameObject
{
public:
	Dorone();
	void setup();

	void update();
	void draw();
	void keyDown();
	void mouseDown();


	void onGround();
	float getRadius();
	void onGoal();
	void setIsMove(bool);
	void setIsDraw(bool);
	void setMemoryTransform(int);
	void memoryClear();

	CameraWork *camera;
	DoroneMemory * dorone_memory;
private:

	void moveFn();

	void move(float, float);
	void up(float);
	void turning(float);

	ci::Vec3f vec;
	ci::Vec3f tergetVec;

	float radius;

	TriMeshRef body;
	TriMeshRef wing;
	MaterialRef matelial;

	std::shared_ptr<ci::gl::Texture> texture;

	std::vector<DroneOneFrame> memory;

	bool is_move;
	bool is_draw;

};