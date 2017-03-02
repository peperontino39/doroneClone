#include "CameraWork.h"

#include "cinder/app/App.h"
#include "cinder/CinderMath.h"
#include "../../System/Utility/Utility.h"
#include "../../System/Interface/Interface.h"
#include "cinder/params/Params.h"
#include "cinder/Vector.h"
#include "cinder/Quaternion.h"
#include "../../System/Easing/Easing.h"
#include "cinder/Easing.h"

using namespace ci;
using namespace ci::app;

void CameraWork::setup()
{
	/*c_Interface.create();
	c_Interface.get()->addParam("terget_center", &terget_center);
	c_Interface.get()->addParam("terget_direction", &terget_direction);
*/

	camera.setPerspective(60, getWindowAspectRatio(), 1, 1000);
	terget_center = Vec3f::zero();
	center = terget_center;
	terget_direction = ci::Vec3f::yAxis() * Quatf(0.01f, 0, 0);
	direction = terget_direction;
	length = 100;

	camera.setCenterOfInterestPoint(terget_center);
	camera.setEyePoint(camera.getCenterOfInterestPoint() + terget_direction);

}

void CameraWork::cameraDrawBegin()
{
	gl::pushMatrices();
	gl::setMatrices(camera);


}

void CameraWork::update()
{

	if (is_move_terget) {
		direction = direction.lerp(0.1f, terget_direction);
		center = center.lerp(0.1f, terget_center);

	}
	camera.setCenterOfInterestPoint(center);
	camera.setEyePoint(camera.getCenterOfInterestPoint() + direction.normalized() * length);

	//camera.setViewDirection(camera.getViewDirection().slerp(0.1f, terget_direction));


}

void CameraWork::draw()
{
	gl::drawCoordinateFrame();

	gl::color(.5f, .5f, .5f);
	drawGrid(50.f, 1.f);
}

void CameraWork::cameraDrawEnd()
{
	gl::popMatrices();
}

void CameraWork::resize()
{
	camera.setAspectRatio(getWindowAspectRatio());
}

void CameraWork::setTransfome(Transform & _transfome, float up)
{
	terget_center = _transfome.position;
	terget_direction = Vec3f(0.f, up, -1.f) * _transfome.rotate;

	//terget_direction += terget_direction * transform.rotate;
	//console() << Vec3f(0, up, -1) *  transform.rotate << std::endl;
	//terget_direction.normalize();
}

void CameraWork::setTransfomeE(Transform & _transfome, float _time, float up)
{
	terget_center = _transfome.position;
	terget_direction = Vec3f(0.f, up, -1.f) * _transfome.rotate;
	setCenterE(terget_center, _time);
	setDirectionE(terget_direction, _time);

}

void CameraWork::setCenterT(ci::Vec3f _cen)
{
	center = _cen;

}

void CameraWork::setDirectionT(ci::Vec3f _dir)
{
	direction = _dir;
}


void CameraWork::setCenter(ci::Vec3f _cen)
{
	terget_center = _cen;
}

void CameraWork::setDirection(ci::Vec3f _dir)
{
	terget_direction = _dir;
}

void CameraWork::setLength(float _len)
{
	length = _len;
}

void CameraWork::setCenterE(ci::Vec3f _val, float _time)
{
	Easing<Vec3f>::clear(center);

	Easing<Vec3f>::apply(center, _val, ci::EaseNone(), _time);
	terget_center = _val;
}

void CameraWork::setDirectionE(ci::Vec3f _val, float _time)
{
	Easing<Vec3f>::clear(direction);

	Easing<Vec3f>::apply(direction, _val, ci::EaseNone(), _time);

	terget_direction = _val;
}

void CameraWork::setLengthE(float _len, float _time)
{
	Easing<float>::clear(length);
	Easing<float>::apply(length, _len, ci::EaseNone(), _time);

}
