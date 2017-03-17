#pragma once
#include "../../GameObject.h"

class ConveyorBase;
typedef std::vector<std::vector<ConveyorBase*>> Conveyor2D;
enum ConveyorDirection;

class BeltConveyor : public GameObject
{
public:
	void draw() override;
	void setup() override;
	void shutdown()override;


	void setSize(const int&, const int&);
	void setSize(const ci::Vec2i &);
	void setDirection(const ci::Vec2i &, const ConveyorDirection&);
	void changeDirection(const ci::Vec2i &);
	
private:

	void clear();
	void setConveyor(const int&, const int&, const ConveyorBase&);

	Conveyor2D conveyor_2d;
	ci::Vec2i size;
};