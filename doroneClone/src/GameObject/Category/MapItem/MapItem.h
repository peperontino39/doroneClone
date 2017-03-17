#pragma once
#include "../../GameObject.h"
#include <list>

class ItemBase;

class MapItem : public GameObject
{
public:
	void setup()override;

	void nonLightDraw() override;
	void shutdown()override;
	void instans(ItemBase*);

	void nullCheck();

private:
	

	std::list<ItemBase*> items;

};