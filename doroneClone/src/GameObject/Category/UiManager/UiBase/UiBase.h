#pragma once
#include "../../../GameObject.h"
#include <map>

class UiBase : public GameObject
{
public:
	void drawUI() override;


	std::map<std::string, UiBase*> uis;

	bool getIsActive();
	void setIsActive(const bool&);

private:
	bool is_active;
	int width;
	int height;
	ci::Vec2f pivot;


};