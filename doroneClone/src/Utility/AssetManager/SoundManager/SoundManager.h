#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/imageIo.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"
#include "cinder/gl/Texture.h"
#include <unordered_map>
using namespace ci;
using namespace ci::app;






class SoundManager
{
public:

	static SoundManager& getm() {
		static SoundManager sm;
		return sm;
	}
	SoundManager();
	~SoundManager();

	template<typename T>
	void set(std::string _key, std::string _path)
	{
		assert(!"‚ ‚ê‚ê");
	}
	template<> void set<audio::BufferPlayerNode>(std::string _key, std::string _path) {
		if (sound.find(_key) == sound.end()) {
			std::shared_ptr<audio::BufferPlayerNode> hoge = ctx->makeNode(new audio::BufferPlayerNode);
			audio::SourceFileRef source = audio::load(loadAsset(_path));
			hoge->loadBuffer(source);
			gain = ctx->makeNode(new audio::GainNode());
			hoge >> gain >> ctx->getOutput();
			sound[_key] = hoge;
		}
	}
	template<> void set<audio::FilePlayerNode>(std::string _key, std::string _path) {
		if (sound.find(_key) == sound.end()) {
			std::shared_ptr<audio::FilePlayerNode> hoge = ctx->makeNode(new audio::FilePlayerNode);
			audio::SourceFileRef source = audio::load(loadAsset(_path));
			hoge->setSourceFile(source);
			gain = ctx->makeNode(new audio::GainNode());
			hoge >> gain >> ctx->getOutput();
			sound[_key] = hoge;
		}
	}

	audio::SamplePlayerNodeRef& get(std::string);

private:

	std::unordered_map<std::string, audio::SamplePlayerNodeRef> sound;

	audio::GainNodeRef gain;
	audio::Context* ctx;
};
#define Sounds SoundManager::getm()