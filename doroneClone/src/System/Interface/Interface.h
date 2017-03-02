#pragma once
#include <map>

#include "../CinderFwd.h"
#include "cinder/Color.h"
#include "cinder/Vector.h"


#define c_Interface c_InterfaceManager::single()

class c_InterfaceManager
{
public:
	void create(
		const std::string& = "Interface",
		const ci::Vec2i& = ci::Vec2i::zero(),
		const ci::Vec2i& = ci::Vec2i(160, 540),
		const ci::ColorA & = ci::ColorA(0.3f, 0.3f, 0.3f, 0.4f)
		);

	ci::params::InterfaceGlRef& get(
		const std::string& = "Interface"
		);
	void pop(std::string);

	void draw();

	
	static c_InterfaceManager & single() {
		static c_InterfaceManager _interface;
		return _interface;
	}
private:

	std::map<std::string,ci::params::InterfaceGlRef> params;
};
