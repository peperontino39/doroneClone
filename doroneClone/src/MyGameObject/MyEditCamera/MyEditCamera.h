#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"

class MyEditCamera : public GameObject
{
public:
	MyEditCamera();
	~MyEditCamera();

	void setup();
	void shutdown();


	void cameraDrawBegin();
	void draw();
	void cameraDrawEnd();

	void mouseDrag();
	void mouseWheel();
	void mouseDown();
	
	ci::Ray getRay();

	void resize();
private:
	ci::MayaCamUI* camera;
};

