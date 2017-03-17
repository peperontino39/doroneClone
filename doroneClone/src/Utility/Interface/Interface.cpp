#include "Interface.h"
#include "cinder/params/Params.h"

void c_InterfaceManager::create(
	const std::string & _title,
	const ci::Vec2i & _pos, 
	const ci::Vec2i & _size, 
	const ci::ColorA & _color)
{
	if (params.find(_title) == params.end()) {

		params.insert(std::make_pair(
			_title,
			ci::params::InterfaceGl::create(_title, _size, _color)
			));
		params[_title]->setPosition(_pos);
	}
}

ci::params::InterfaceGlRef & c_InterfaceManager::get(const std::string & _title)
{
	return params[_title];
}

void c_InterfaceManager::pop(std::string _key)
{
	auto it = params.find(_key);
	if (it != params.end())
		params.erase(it);
}

void c_InterfaceManager::draw()
{
	for (auto & it : params) {
		it.second->draw();
	}
}


