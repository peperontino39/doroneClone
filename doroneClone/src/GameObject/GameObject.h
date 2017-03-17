#pragma once
#include "../Utility/Transform/Transform.h"

class SceneBase;

class GameObject
{
public:

	GameObject() {};
	virtual ~GameObject() {};

	virtual void setup() {};

	virtual void update() {};

	virtual void cameraDrawBegin() {};
	virtual void lightDrawBegin() {};
	virtual void draw() {};
	virtual void lightDrawEnd() {};
	virtual void nonLightDraw() {};
	virtual void cameraDrawEnd() {};
	virtual void drawUI() {};
	virtual void sceneCange(SceneBase& _scene) {};


	virtual void shutdown() {};

	virtual void mouseDown() {};
	virtual void mouseUp() {};
	virtual void mouseWheel() {};
	virtual void mouseMove() {};
	virtual void mouseDrag() {};

	virtual void keyDown() {};
	virtual void keyUp() {};

	virtual void resize() {};
	Transform transform;
protected:

private:

};

typedef std::shared_ptr<GameObject> GameObjectRef;