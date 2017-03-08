#include "SceneManager.h"
#include "cinder/app/App.h"
#include "cinder/Vector.h"

#include "../Scene/StageSelect/StageSelect.h"

void SceneManager::setup()
{
	camera_ortho.setOrtho(
		ci::app::getWindowWidth() / 2,
		ci::app::getWindowWidth() / -2,
		ci::app::getWindowHeight() / 2,
		ci::app::getWindowHeight() / -2, 1, 1000);

	camera_ortho.setEyePoint(-ci::Vec3f::zAxis() * 500);
	camera_ortho.setCenterOfInterestPoint(ci::Vec3f::zAxis() * 500);

	nowScene = new StageSelect();

	nowScene->onCreate();
	nowScene->setup();
}

void SceneManager::update()
{
	SceneBase* next = nowScene->nextScene();
	if (next != nullptr) {
		nowScene->shutdown();
		delete nowScene;
		nowScene = next;
		nowScene->onCreate();
		nowScene->setup();
	}

	nowScene->update();
}

void SceneManager::draw()
{
	ci::gl::clear();

	ci::gl::enableDepthRead();
	ci::gl::enableAlphaBlending();
	ci::gl::enable(GL_CULL_FACE);
	ci::gl::enable(GL_LIGHTING);

	nowScene->cameraDrawBegin();
	nowScene->lightDrawBegin();
	nowScene->draw();

	nowScene->lightDrawEnd();
	nowScene->cameraDrawEnd();

	ci::gl::pushMatrices();
	ci::gl::setMatrices(camera_ortho);

	
	ci::gl::disableDepthRead();
	ci::gl::disableDepthWrite();
	ci::gl::disable(GL_CULL_FACE);
	ci::gl::disable(GL_LIGHTING);

	nowScene->drawUI();

	ci::gl::popMatrices();
}

void SceneManager::shutdown()
{
	nowScene->shutdown();
	delete nowScene;
}

void SceneManager::mouseDown()
{
	nowScene->mouseDown();
}

void SceneManager::mouseUp()
{
	nowScene->mouseUp();
}

void SceneManager::mouseWheel()
{

	nowScene->mouseWheel();
}

void SceneManager::mouseMove()
{

	nowScene->mouseMove();
}

void SceneManager::mouseDrag()
{
	nowScene->mouseDrag();
}

void SceneManager::keyDown()
{
	nowScene->keyDown();
}

void SceneManager::keyUp()
{
	nowScene->keyUp();
}

void SceneManager::resize()
{
	nowScene->resize();
	camera_ortho.setOrtho(
		ci::app::getWindowWidth() / 2,
		ci::app::getWindowWidth() / -2,
		ci::app::getWindowHeight() / 2,
		ci::app::getWindowHeight() / -2, 1, 1000);
}


