#pragma once
#include "../EasingInfo/EasingInfo.h"
#include <List>


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