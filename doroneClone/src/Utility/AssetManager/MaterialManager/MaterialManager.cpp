#include "MaterialManager.h"
#include "cinder/Json.h"
#include "cinder/app/App.h"
#include "cinder/gl/Material.h"
#include <filesystem>
#include "../../Utility/Utility.h"

MaterialManager::MaterialManager()
{
	set("default", "Material/default.json");
	std::string directory_name = "Material";
	for (std::tr2::sys::directory_iterator it(ci::app::getAssetPath(directory_name).string()), end; it != end; it++) {
		//ci::app::console() << NonExtensionFileName(FileName(it->path().string())) << std::endl;
		std::string file_name = FileName(it->path().string());
		set(NonExtensionFileName(file_name),
			directory_name + "/" + file_name);
	}
}

MaterialManager::~MaterialManager()
{
}

ci::ColorA getJtoC(const ci::JsonTree& _json) {
	return ci::ColorA(
		_json.getValueAtIndex<float>(0),
		_json.getValueAtIndex<float>(1),
		_json.getValueAtIndex<float>(2),
		_json.getValueAtIndex<float>(3)
		);
}


void MaterialManager::set(std::string _key, std::string _path)
{
	if (!isHave(_key)) {
		MaterialRef mat = std::make_shared<ci::gl::Material>();
		ci::JsonTree json(ci::app::loadAsset(_path));
		mat->setAmbient(getJtoC(json["Ambient"]));
		mat->setDiffuse(getJtoC(json["Diffuse"]));
		mat->setSpecular(getJtoC(json["Specular"]));
		mat->setShininess(json.getValueForKey<float>("Shininess"));
		mat->setEmission(getJtoC(json["Emission"]));
		materials[_key] = mat;
		//std::string path = "../assets/Stage/" "hoge.json";
		//json.write(path);
	}
}

MaterialRef MaterialManager::get(std::string key)
{
	return materials[key];
}

bool MaterialManager::isHave(std::string _key)
{
	return materials.find(_key) != materials.end();
}
