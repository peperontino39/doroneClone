#include "Transform.h"

Transform::Transform()
{
	position = ci::Vec3f::zero();
	rotate = ci::Quatf::identity();
	scale = ci::Vec3f::one();
}

Transform::Transform(ci::Vec3f & position_)
{
	position = position_;
	rotate = ci::Quatf::identity();
	scale = ci::Vec3f::one();
}

Transform::Transform(ci::Vec3f & position_, ci::Quatf & rotate_)
{
	position = position_;
	rotate = rotate_;
	scale = ci::Vec3f::one();
}

Transform::Transform(ci::Vec3f & position_, ci::Quatf & rotate_, ci::Vec3f & scale_)
{
	position = position_;
	rotate = rotate_;
	scale = scale_;
}

ci::Matrix44f Transform::getMultiMatrix()
{
	return 
		ci::Matrix44f::createTranslation(position)
		* rotate.toMatrix44()
		* ci::Matrix44f::createScale(scale);
}




