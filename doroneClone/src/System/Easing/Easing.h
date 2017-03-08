#pragma once
#include "cinder/app/App.h"
#include <unordered_map>
#include "cinder/CinderMath.h"
#include "EasingInfos/EasingInfos.h"


template <class T>
class Easing
{
public:
	static void update() {

		for (auto it = easingInfos().begin();
		it != easingInfos().end();
			)
		{
			if (!it->second.update()) {
				it = easingInfos().erase(it);
			}
			else {
				it++;
			}
		}
	}
	template <class T>
	static void apply(
		T& _terget,
		T _endValue,
		std::function<float(float)> _easeFunction,
		float _time = 1.f)
	{

		easingInfos()[&_terget].apply(_terget, _endValue, _easeFunction, _time);
	}

	template <class T>
	static void clear(T& _terget)
	{
		auto it = easingInfos().find(&_terget);
		if (it == easingInfos().end())return;
		easingInfos().erase(it);
	}

private:
	static std::unordered_map <void*, EasingInfos<T>>&  easingInfos();

};

template<class T>
inline std::unordered_map<void*, EasingInfos<T>>& Easing<T>::easingInfos()
{
	static std::unordered_map <void*, EasingInfos<T>>  _easingInfos;
	return _easingInfos;
}


