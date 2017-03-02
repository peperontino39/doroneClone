#include "StageCreate.h"
#include "../../MyGameObject/MyEditCamera/MyEditCamera.h"
#include "../../MyGameObject/StageEdit/StageEdit.h"
#include "cinder/Ray.h"
#include "../../MyGameObject/MyLight/MyLight.h"
#include "../../Scene/GameMain/GameMain.h"
#include "../../System/Input/Input.h"
#include "../../Scene/MaterialCreate/MaterialCreate.h"
#include "../../Scene/StageSelect/StageSelect.h"


void StageCreate::onCreate()
{
	MyEditCamera* camera = Instantiate(new MyEditCamera());
	StageEdit* stage_edit = Instantiate(new StageEdit());
	MyLight* myLight = Instantiate(new MyLight());


	stage_edit->rayFn = std::bind(&MyEditCamera::getRay, camera);

	nextScene = [&] {
		SceneBase*  next = nullptr;
		if (c_Input.getKeyPush(ci::app::KeyEvent::KEY_1)) {
			next = new StageSelect();
		}
		if (c_Input.getKeyPush(ci::app::KeyEvent::KEY_3)) {
			next = new MaterialCreate();
		}

		return next;
	};
}
