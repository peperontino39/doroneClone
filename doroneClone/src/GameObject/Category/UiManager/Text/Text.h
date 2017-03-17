#pragma once
#include "../UiBase/UiBase.h"
#include "cinder/Text.h"


class Text : public UiBase {



	void drawUI()override;

private:
	ci::TextBox textbox;

};

