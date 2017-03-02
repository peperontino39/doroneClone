#include "MaterialCreate.h"
#include "../../MyGameObject/MyEditCamera/MyEditCamera.h"
#include "../../MyGameObject/MaterialEdit/MaterialEdit.h"
#include "../../Scene/StageCreate/StageCreate.h"
#include "../../System/Input/Input.h"


void MaterialCreate::onCreate()
{

	MaterialEdit* material_edit = Instantiate(new MaterialEdit());
	MyEditCamera* camera = Instantiate(new MyEditCamera());


	nextScene = [&] {
		SceneBase*  next = nullptr;
		if (c_Input.getKeyPush(ci::app::KeyEvent::KEY_2)) {
			next = new StageCreate();
		}
		return next;
	};
}
