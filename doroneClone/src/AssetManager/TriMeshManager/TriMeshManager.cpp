#include "TriMeshManager.h"
#include "cinder/imageIo.h"
#include "cinder/ObjLoader.h"       
#include "cinder/TriMesh.h" 
#include "cinder/app/AppNative.h"
#include <filesystem>
#include "../../System/Utility/Utility.h"




TriMeshManager::TriMeshManager()
{
	std::string directory_name = "model";
	for (std::tr2::sys::directory_iterator it(ci::app::getAssetPath(directory_name).string()), end; it != end; it++) {
		//ci::app::console() << NonExtensionFileName(FileName(it->path().string())) << std::endl;
		std::string file_name = FileName(it->path().string());
		set(NonExtensionFileName(file_name),
			directory_name + "/" + file_name);
	}
}

TriMeshManager::~TriMeshManager()
{
}

void TriMeshManager::set(std::string _key, std::string _path)
{
	if (trimeshs.find(_key) == trimeshs.end()) {
		ci::ObjLoader loader = ci::app::loadAsset(_path);
		trimeshs[_key] = std::make_shared<cinder::TriMesh>(cinder::TriMesh());
			loader.load(&(*trimeshs[_key]),
				boost::logic::indeterminate, boost::logic::indeterminate,
				false);
	}
}

std::shared_ptr<cinder::TriMesh> TriMeshManager::get(std::string _key)
{
	return trimeshs[_key];
}

bool TriMeshManager::isHave(std::string _key)
{
	return trimeshs.find(_key) != trimeshs.end();
}

