#include "MyEditCamera.h"
#include "cinder/MayaCamUI.h"
#include "cinder/app/App.h"
#include "../../../Utility/Utility/Utility.h"
#include "../../../Utility/Input/Input.h"

using namespace ci;
using namespace ci::app;

MyEditCamera::MyEditCamera()
{
	
	CameraPersp cam;
	cam.setPerspective(60, getWindowAspectRatio(), 1, 1000);
	cam.setCenterOfInterest(20);
	camera = new ci::MayaCamUI(cam);
}

MyEditCamera::~MyEditCamera()
{

}

void MyEditCamera::setup()
{
}

void MyEditCamera::shutdown()
{
	delete camera;
}

void MyEditCamera::cameraDrawBegin()
{
	gl::pushMatrices();
	gl::setMatrices(camera->getCamera());

	
}

void MyEditCamera::draw()
{
	gl::disable(GL_LIGHTING);

	gl::drawCoordinateFrame();

	gl::color(.5f, .5f, .5f);
	drawGrid(50.f, 1.f);

	gl::enable(GL_LIGHTING);

}

void MyEditCamera::cameraDrawEnd()
{
	gl::popMatrices();
}

void MyEditCamera::mouseDrag()
{
	camera->mouseDrag(c_Input.getMousePos(), 
		c_Input.getMousePress(MouseEvent::RIGHT_DOWN),
		c_Input.getMousePress(MouseEvent::MIDDLE_DOWN), 
		false);

}

void MyEditCamera::mouseWheel()
{
	CameraPersp cam = camera->getCamera();
	cam.setEyePoint(cam.getEyePoint()
		+ cam.getViewDirection()
		* c_Input.getWheelIncrement());
	camera->setCurrentCam(cam);
	
}

void MyEditCamera::mouseDown()
{
	camera->mouseDown(c_Input.getMousePos());
}

ci::Ray MyEditCamera::getRay()
{
	Vec2f pos = c_Input.getMousePos();

	pos.x = pos.x / float(getWindowWidth());
	pos.y = 1.0f - pos.y / float(getWindowHeight());

	return camera->getCamera().generateRay(pos.x, pos.y,
		camera->getCamera().getAspectRatio());
}

void MyEditCamera::resize()
{
	CameraPersp cam = camera->getCamera();
	cam.setAspectRatio(getWindowAspectRatio());
	camera->setCurrentCam(cam);
}
