#include "SoundManager.h"

SoundManager::SoundManager()
{
	ctx = audio::master();
	ctx->enable();
}

SoundManager::~SoundManager()
{

}

audio::SamplePlayerNodeRef& SoundManager::get(std::string _path)
{
	return sound[_path];
}


