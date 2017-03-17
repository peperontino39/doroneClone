#pragma once
#include <functional>
#include <list>

#define c_Coroutine Coroutine::single() 

class CoroutinInfo
{
public:
	CoroutinInfo(float _time, std::function<void()> _func);
	float startTime;
	float time;
	std::function<void()> func;
private:

};

class Coroutine
{
public:

	void operator ()(float, std::function<void()>);


	void registerUpdate();
	static Coroutine& single() {
		static Coroutine coroutine;
		return coroutine;
	}
private:
	std::list<CoroutinInfo> coroutinInfos;
};


