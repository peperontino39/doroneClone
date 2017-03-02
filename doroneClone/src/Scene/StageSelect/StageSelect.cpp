#include "StageSelect.h"
#include "../../MyGameObject/Buttons/Buttons.h"
#include  "../../Scene/GameMain/GameMain.h"
#include "../../System/Input/Input.h"
#include "../../Scene/StageCreate/StageCreate.h"
#include "../../AssetManager/SoundManager/SoundManager.h"

void StageSelect::onCreate()
{
	Buttons* buttons = Instantiate(new Buttons());

	isnext = std::bind(&Buttons::isOk, buttons);
	stage_num = std::bind(&Buttons::getStageNum, buttons);
	
	nextScene = [&] {
		SceneBase*  next = nullptr;
		if (isnext()) {
			Sounds.get("se")->start();
			next = new GameMain(stage_num());
		}
		if (c_Input.getKeyPush(ci::app::KeyEvent::KEY_2)) {
			next = new StageCreate();
		}

		return next;
	};

}
