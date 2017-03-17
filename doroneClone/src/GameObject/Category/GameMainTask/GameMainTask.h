#pragma once
#include "../../GameObject.h"

class Map;
class MyEditCamera;
class MapItem;
class ItemBase;

class GameMainTask : public GameObject
{
public:

	void setup()override;
	void update()override;
	void draw()override;

	void mouseDown()override;
	void mouseMove()override;

	void keyDown()override;

	Map* map;
	MyEditCamera* camera;
	MapItem* map_item;

private:

	void createItem(ItemBase*);
	ItemBase* test;
};