#include "TextureManager.h"
#include <filesystem>
#include "../../System/Utility/Utility.h"


TextureManager::TextureManager()
{
	std::string directory_name = "Texture";
	for (std::tr2::sys::directory_iterator it(ci::app::getAssetPath(directory_name).string()), end; it != end; it++) {
		//ci::app::console() << NonExtensionFileName(FileName(it->path().string())) << std::endl;
		std::string file_name = FileName(it->path().string());
		set(NonExtensionFileName(file_name),
			directory_name + "/" + file_name);
	}
}

void TextureManager::set(std::string _key, std::string _path)
{
	if (textures.find(_key) == textures.end()) {
		textures[_key] = std::make_shared<cinder::gl::Texture>(cinder::loadImage(ci::app::loadAsset(_path)));
	}
}

cinder::gl::TextureRef TextureManager::get(std::string _key)
{
	return textures[_key];
}

bool TextureManager::isHave(std::string _key)
{
	return textures.find(_key) != textures.end();
}

