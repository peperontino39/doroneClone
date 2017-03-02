#pragma once
#include "../SceneBase/SceneBase.h"

class StageSelect : public SceneBase
{
public:
	void onCreate() override;
	std::function<bool()> isnext;
	std::function<int()> stage_num;


};


