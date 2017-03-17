#include "UiBase.h"
#include "cinder/gl/gl.h"

void UiBase::drawUI()
{
	ci::gl::pushMatrices();
	ci::gl::multModelView(transform.getMultiMatrix());
	for (auto& ui : uis)
	{
		
		ui.second->drawUI();
	}

	ci::gl::popMatrices();

}

bool UiBase::getIsActive()
{
	return is_active;
}

void UiBase::setIsActive(const bool & _is_active)
{
	is_active = _is_active;
}
