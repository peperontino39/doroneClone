#pragma once
#include "cinder/Camera.h"

class SceneBase;

class SceneManager
{
public:

	void setup();
	void update();
	void draw();
	void shutdown();

	void mouseDown();
	void mouseUp();
	void mouseWheel();
	void mouseMove();
	void mouseDrag();

	void keyDown();
	void keyUp();

	void resize();

private:

	ci::CameraOrtho camera_ortho;
	SceneBase* nowScene;

};

