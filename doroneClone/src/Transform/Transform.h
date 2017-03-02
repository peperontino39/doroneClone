#pragma once
#include "../System/CinderFwd.h"
#include "cinder/Quaternion.h"

class Transform
{
public:
	Transform();
	Transform(ci::Vec3f&);
	Transform(ci::Vec3f&, ci::Quatf&);
	Transform(ci::Vec3f&, ci::Quatf&, ci::Vec3f&);

	ci::Matrix44f getMultiMatrix();

	ci::Vec3f position;
	ci::Quatf rotate;
	ci::Vec3f scale;

private:
};

typedef std::shared_ptr<Transform> TransformRef;
