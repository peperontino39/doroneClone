#include "Coroutine.h"
#include "cinder/app/App.h"

CoroutinInfo::CoroutinInfo(float _time, std::function<void()> _func)
{
	startTime = ci::app::getElapsedSeconds();
	time = _time;
	func = _func;
}

void Coroutine::operator()(float _time, std::function<void()> _func)
{
	coroutinInfos.push_back(CoroutinInfo(_time, _func));
}

void Coroutine::registerUpdate()
{
	for (auto cor = coroutinInfos.begin(); cor != coroutinInfos.end();) {
		if (cor->time < (ci::app::getElapsedSeconds() - cor->startTime)) {
			cor->func();
			cor = coroutinInfos.erase(cor);
			continue;
		}
		cor++;
	}
}


