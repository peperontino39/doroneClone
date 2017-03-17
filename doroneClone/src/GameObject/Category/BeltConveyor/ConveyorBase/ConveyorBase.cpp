#include "ConveyorBase.h"
#include "../../../../Utility/AssetManager/TextureManager/TextureManager.h" 
#include "../../../../Utility/Utility/Utility.h" 


#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

ConveyorBase::ConveyorBase()
{
	setDirection(ConveyorDirection::UP);
}

ConveyorBase::ConveyorBase(const ConveyorDirection& _direction)
{
	setDirection(_direction);
}

void ConveyorBase::draw()
{

}

ConveyorDirection ConveyorBase::getDirection()
{
	return direction;
}

void ConveyorBase::setDirection(const ConveyorDirection & _direction)
{

	direction = _direction;
	switch (direction)
	{
	case ConveyorDirection::UP:
		transform.rotate = Quatf(0, 0, -M_PI / 2);
		break;
	case ConveyorDirection::DOWN:
		transform.rotate = Quatf(0, 0, M_PI / 2);
		break;
	case ConveyorDirection::RIGHT:
		transform.rotate = Quatf(0, 0, M_PI);
		break;
	case ConveyorDirection::LEFT:
		transform.rotate = Quatf::identity();
		break;
	}
}

void ConveyorBase::changeDirection()
{
	auto _direction = ConveyorDirection((direction + 1) % ConveyorDirection::NON);
	setDirection(_direction);
}

ci::Vec2i ConveyorBase::directionToVec()
{
	switch (direction)
	{
	case UP:return Vec2i::yAxis();
	case DOWN:return -Vec2i::yAxis();
	case RIGHT:return Vec2i::xAxis();
	case LEFT:return -Vec2i::xAxis();

	}
	return Vec2i::zero();
}


