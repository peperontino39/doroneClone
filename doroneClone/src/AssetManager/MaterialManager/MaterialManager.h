#pragma once
#include "../../System/CinderFwd.h"
#include <unordered_map>

class MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();

	void set(std::string, std::string);
	MaterialRef get(std::string);
	bool isHave(std::string);

	static MaterialManager & single() {
		static MaterialManager material_manager;
		return material_manager;
	}

private:
	std::unordered_map<std::string, MaterialRef> materials;
};


#define Materials MaterialManager::single()