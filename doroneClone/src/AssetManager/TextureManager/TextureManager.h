#pragma once
#include "cinder/gl/Texture.h"
#include "cinder/imageIo.h"
#include "cinder/app/AppNative.h"
#include <unordered_map>


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

#define Textures TextureManager::single()
