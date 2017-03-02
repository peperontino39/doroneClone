#pragma once
#include "../SceneBase/SceneBase.h"

class GameMain : public SceneBase
{
public:
	GameMain(int);

	void onCreate() override;
	int stage_num;
	bool* is_end;
};



