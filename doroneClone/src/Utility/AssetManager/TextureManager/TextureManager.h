#pragma once
#include <unordered_map>
#include "../../CinderFwd.h"
#include "cinder/gl/Texture.h"

class TextureManager
{
public:
	static TextureManager& single() {
		static TextureManager tm;
		return tm;
	}
	TextureManager();
	void set(std::string, std::string);
	cinder::gl::TextureRef get(std::string);
	bool isHave(std::string);


private:
	std::unordered_map<std::string, cinder::gl::TextureRef> textures;

};

#define TextureM TextureManager::single()
