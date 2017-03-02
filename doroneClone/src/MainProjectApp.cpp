#include "cinder/app/AppNative.h"  
#include <boost/any.hpp>
#include "System/Easing/Easing.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"
#include "AssetManager/TriMeshManager/TriMeshManager.h"
#include "AssetManager/TextureManager/TextureManager.h"
#include "cinder/MayaCamUI.h"
#include "System/Utility/Utility.h"
#include "Scene/SceneBase/SceneBase.h"
#include "Scene/GameMain/GameMain.h"
#include "Scene/StageCreate/StageCreate.h"

#include "System/Input/Mouse/Mouse.h"
#include "System/Input/Key/Key.h"
#include "System/Coroutine/Coroutine.h"
#include "System/Interface/Interface.h"
#include "AssetManager/MaterialManager/MaterialManager.h"
#include "System/Easing/Easing.h"
#include "cinder/Camera.h"
#include "Scene/StageSelect/StageSelect.h"
#include "AssetManager/SoundManager/SoundManager.h"

using namespace ci;
using namespace ci::app;

class MainProjectApp : public AppNative {
public:
	void prepareSettings(Settings *settings);

	void	setup();
	void	shutdown();

	void	update();
	void	draw();

	void	mouseDown(MouseEvent event);
	void	mouseUp(MouseEvent event);
	void	mouseWheel(MouseEvent event);
	void	mouseMove(MouseEvent event);
	void	mouseDrag(MouseEvent event);

	void	touchesBegan(TouchEvent event);
	void	touchesMoved(TouchEvent event);
	void	touchesEnded(TouchEvent event);

	void	keyDown(KeyEvent event);
	void	keyUp(KeyEvent event);

	void	resize();
	void	fileDrop(FileDropEvent event);
private:
	CameraOrtho camera_ortho;
	SceneBase* nowScene;
};

void MainProjectApp::prepareSettings(Settings * settings)
{
	settings->setWindowSize(960, 540);

}

//ci::Vec3f _val;
//ci::Vec3f center;
//float _time;


void MainProjectApp::setup()
{
	Materials;
	TriMeshs;
	Textures;
	Sounds;

	Sounds.set<audio::FilePlayerNode>("bgm", "Sound/bgm_maoudamashii_piano09.wav");
	Sounds.set<audio::FilePlayerNode>("se", "Sound/clear.wav");
	Sounds.set<audio::FilePlayerNode>("dame", "Sound/se_maoudamashii_system18.wav");
	
	Sounds.get("bgm")->start();
	Sounds.get("bgm")->setLoopEnabled(1);


	camera_ortho.setOrtho(getWindowWidth() / 2, getWindowWidth() / -2,
		getWindowHeight() / 2, getWindowHeight() / -2, 1, 1000);
	camera_ortho.setEyePoint(-Vec3f::zAxis() * 500);
	camera_ortho.setCenterOfInterestPoint(Vec3f::zAxis() * 500);


	//Easing<Vec3f>::apply(center, _val, ci::EaseNone(), _time);

	//nowScene = new StageCreate();
	//nowScene = new GameMain(3);
	nowScene =new StageSelect();

	nowScene->onCreate();
	nowScene->setup();

	gl::enable(GL_CULL_FACE);
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
}

void MainProjectApp::shutdown()
{
	nowScene->shutdown();
	delete nowScene;
}

void MainProjectApp::update()
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
	c_Coroutine.registerUpdate();
	Easing<Vec3f>::update();
	Easing<float>::update();

	//Easing<float>::update();

	//console() << getAverageFps() << std::endl;
}

void MainProjectApp::draw()
{

	gl::clear();

	gl::enableDepthRead();
	gl::enableAlphaBlending();
	gl::enable(GL_CULL_FACE);
	gl::enable(GL_LIGHTING);

	nowScene->cameraDrawBegin();
	nowScene->lightDrawBegin();
	nowScene->draw();

	nowScene->lightDrawEnd();
	nowScene->cameraDrawEnd();

	gl::pushMatrices();
	gl::setMatrices(camera_ortho);

	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::disable(GL_LIGHTING);

	nowScene->drawUI();

	gl::popMatrices();

	c_Interface.draw();
	c_Mouse.registerLast();
	c_Key.registerLast();
}

void MainProjectApp::mouseDown(MouseEvent event)
{
	c_Mouse.registerDown(event);
	nowScene->mouseDown();
}

void MainProjectApp::mouseUp(MouseEvent event)
{
	c_Mouse.registerUp(event);

	nowScene->mouseUp();
}

void MainProjectApp::mouseWheel(MouseEvent event)
{
	c_Mouse.registerWheel(event);


	nowScene->mouseWheel();
}

void MainProjectApp::mouseMove(MouseEvent event)
{
	c_Mouse.registerMove(event);

	nowScene->mouseMove();
}

void MainProjectApp::mouseDrag(MouseEvent event)
{
	c_Mouse.registerDrag(event);

	nowScene->mouseDrag();
}

void MainProjectApp::touchesBegan(TouchEvent event)
{

}

void MainProjectApp::touchesMoved(TouchEvent event)
{
}

void MainProjectApp::touchesEnded(TouchEvent event)
{
}

void MainProjectApp::keyDown(KeyEvent event)
{
	//console() <<  event.getCode() << std::endl;
	c_Key.registerDown(event);
	nowScene->keyDown();

}

void MainProjectApp::keyUp(KeyEvent event)
{
	c_Key.registerUp(event);
	nowScene->keyUp();
}

void MainProjectApp::resize()
{
	nowScene->resize();
	camera_ortho.setOrtho(getWindowWidth() / 2, getWindowWidth() / -2,
		getWindowHeight() / 2, getWindowHeight() / -2, 1, 1000);
}

void MainProjectApp::fileDrop(FileDropEvent event)
{
}


CINDER_APP_NATIVE(MainProjectApp, RendererGl)
