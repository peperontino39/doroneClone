#include "cinder/app/AppNative.h"  


#include "Utility/AssetManager/TriMeshManager/TriMeshManager.h"
#include "Utility/AssetManager/TextureManager/TextureManager.h"
#include "Utility/AssetManager/MaterialManager/MaterialManager.h"

#include "Utility/Input/Mouse/Mouse.h"
#include "Utility/Input/Key/Key.h"

#include "Utility/Easing/Easing.h"
#include "Utility/Coroutine/Coroutine.h"
#include "Utility/Interface/Interface.h"

#include "Scene/SceneManager/SceneManager.h"

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

	SceneManager scene_manager;
};

void MainProjectApp::prepareSettings(Settings * settings)
{
	settings->setWindowSize(960, 540);

}


void MainProjectApp::setup()
{

	Materials;
	TriMeshs;
	TextureM;

	scene_manager.setup();

	gl::enable(GL_CULL_FACE);
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
}

void MainProjectApp::shutdown()
{
	scene_manager.shutdown();
}

void MainProjectApp::update()
{

	//console() << getAverageFps() << std::endl;
	scene_manager.update();

	c_Coroutine.registerUpdate();
	Easing<Vec3f>::update();
	Easing<Vec2f>::update();
	Easing<float>::update();
}

void MainProjectApp::draw()
{

	scene_manager.draw();

	c_Interface.draw();
	c_Mouse.registerLast();
	c_Key.registerLast();
}

void MainProjectApp::mouseDown(MouseEvent event)
{
	c_Mouse.registerDown(event);

	scene_manager.mouseDown();
}

void MainProjectApp::mouseUp(MouseEvent event)
{
	c_Mouse.registerUp(event);

	scene_manager.mouseUp();
}

void MainProjectApp::mouseWheel(MouseEvent event)
{
	c_Mouse.registerWheel(event);

	scene_manager.mouseWheel();
}

void MainProjectApp::mouseMove(MouseEvent event)
{
	c_Mouse.registerMove(event);

	scene_manager.mouseMove();
}

void MainProjectApp::mouseDrag(MouseEvent event)
{
	c_Mouse.registerDrag(event);

	scene_manager.mouseDrag();
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
	c_Key.registerDown(event);

	scene_manager.keyDown();
}

void MainProjectApp::keyUp(KeyEvent event)
{
	c_Key.registerUp(event);

	scene_manager.keyUp();
}

void MainProjectApp::resize()
{
	scene_manager.resize();
}

void MainProjectApp::fileDrop(FileDropEvent event)
{
}


CINDER_APP_NATIVE(MainProjectApp, RendererGl)
