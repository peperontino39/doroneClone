#pragma once
#include "../../../GameObject.h"


enum ConveyorDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NON
};

class ConveyorBase : public GameObject
{
public:

	ConveyorBase();
	ConveyorBase(const ConveyorDirection&);
	void draw()override;

	ConveyorDirection getDirection();
	
	void setDirection(const ConveyorDirection&);
	void changeDirection();
	ci::Vec2i directionToVec();

protected:
	ConveyorDirection  direction;

};

