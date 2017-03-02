#pragma once
#include <unordered_map>
#include <functional>
#include <boost/any.hpp>
#include "cinder/CinderMath.h"
#include "cinder/app/App.h"

template <class T>
class EasingInfo
{
public:
	EasingInfo(
		T _beginValue,
		T _endValue,
		float _startTime,
		float _endTime,
		std::function<float(float)> _easeFunction) {

		easeFunction = _easeFunction;

		startTime = _startTime;
		endTime = _endTime;
		beginValue = _beginValue;
		endValue = _endValue;
	};
	//
	T getValue(float time) {
		return getLerpValue((time - startTime) / (endTime - startTime));
	}
	T getLerpValue(float t) {
		return lerp(beginValue, endValue, easeFunction(t));
	}


	std::function<float(float)> easeFunction;
	float startTime;
	float endTime;
	T beginValue;
	T endValue;
};

template <class T>
class EasingInfos
{

public:
	bool update() {
		if (easingInfos.size() == 0)
			return false;

		*target = easingInfos.begin()->getValue(getElapsedSeconds());
		if (easingInfos.begin()->endTime < getElapsedSeconds())
		{
			*target = easingInfos.begin()->endValue;
			easingInfos.erase(easingInfos.begin());
		}
		return true;
	}
	void apply(
		T& _terget,
		T _endValue,
		std::function<float(float)> _easeFunction,
		float _time
		) {
		if (easingInfos.size() == 0) {
			target = &_terget;
			startTime = getElapsedSeconds();
			easingInfos.push_back(EasingInfo<T>(
				_terget,
				_endValue,
				startTime,
				startTime + _time,
				_easeFunction));
		}
		else
		{
			easingInfos.push_back(EasingInfo<T>(
				easingInfos.back().endValue,
				_endValue,
				easingInfos.back().endTime,
				easingInfos.back().endTime + _time,
				_easeFunction));
		}
	}
private:
	T* target;
	float startTime;
	std::list<EasingInfo<T>> easingInfos;
};


template <class T>
class Easing
{
public:
	static void update() {
		//console() << easingInfos().size() << std::endl;

		
		for (auto it = easingInfos().begin();
		it != easingInfos().end();
			)
		{
			if (!it->second.update()) {
				it = easingInfos().erase(it);
			}
			else{
				it++;
			}
		}
	}
	template <class T>
	static void apply(
		T& _terget,
		T _endValue,
		std::function<float(float)> _easeFunction,
		float _time = 1.f) {

		easingInfos()[&_terget].apply(_terget, _endValue, _easeFunction, _time);
	}

	template <class T>
	static void clear(T& _terget){
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
