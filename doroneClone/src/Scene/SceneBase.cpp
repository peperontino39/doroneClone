#include "SceneBase.h"
#include "../GameObject/GameObject.h"

void SceneBase::onCreate()
{
}

void SceneBase::setup()
{
	for (auto& obj : gameObjects) { obj->setup(); }
}

void SceneBase::update()
{
	for (auto& obj : gameObjects) { obj->update(); }
}

void SceneBase::cameraDrawBegin()
{
	for (auto& obj : gameObjects) { obj->cameraDrawBegin(); }
}

void SceneBase::lightDrawBegin()
{
	for (auto& obj : gameObjects) { obj->lightDrawBegin(); }
}


void SceneBase::draw()
{
	for (auto& obj : gameObjects) { obj->draw(); }
}

void SceneBase::cameraDrawEnd()
{
	for (auto& obj : gameObjects) { obj->cameraDrawEnd(); }
}

void SceneBase::lightDrawEnd()
{
	for (auto& obj : gameObjects) { obj->lightDrawEnd(); }
}

void SceneBase::nonLightDraw()
{
	for (auto& obj : gameObjects) { obj->nonLightDraw(); }
}

void SceneBase::drawUI()
{
	for (auto& obj : gameObjects) { obj->drawUI(); }
}



void SceneBase::shutdown()
{
	for (auto& obj : gameObjects) {
		obj->shutdown();
	}
	for (auto& obj : gameObjects) {
		delete obj;
	}

}

void SceneBase::mouseDown()
{
	for (auto& obj : gameObjects) { obj->mouseDown(); }
}

void SceneBase::mouseUp()
{
	for (auto& obj : gameObjects) { obj->mouseUp(); }

}

void SceneBase::mouseWheel()
{
	for (auto& obj : gameObjects) { obj->mouseWheel(); }
}

void SceneBase::mouseMove()
{
	for (auto& obj : gameObjects) { obj->mouseMove(); }
}

void SceneBase::mouseDrag()
{
	for (auto& obj : gameObjects) { obj->mouseDrag(); }
}

void SceneBase::keyDown()
{
	for (auto& obj : gameObjects) { obj->keyDown(); }
}

void SceneBase::keyUp()
{
	for (auto& obj : gameObjects) { obj->keyUp(); }
}

void SceneBase::resize()
{
	for (auto& obj : gameObjects) { obj->resize(); }
}

void SceneBase::create(GameObject* obj)
{
	gameObjects.push_back(obj);
}


