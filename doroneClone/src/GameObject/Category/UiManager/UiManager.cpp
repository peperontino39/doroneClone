#include "UiManager.h"
#include "UiBase/UiBase.h"

void UiManager::drawUI()
{
	for (auto& ui : uis)
	{
		ui.second->drawUI();
	}
}
