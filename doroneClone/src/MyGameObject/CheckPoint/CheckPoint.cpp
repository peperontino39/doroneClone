#include "CheckPoint.h"
#include "cinder/gl/gl.h"
#include "../../AssetManager/TriMeshManager/TriMeshManager.h"
#include "../../AssetManager/TextureManager/TextureManager.h"
#include "../../AssetManager/MaterialManager/MaterialManager.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/Texture.h"
#include "cinder/CinderMath.h"
#include "cinder/Rand.h"
#include "../../MyGameObject/Dorone/Dorone.h"

using namespace ci;
using namespace ci::app;


void CheckPoint::setup()
{
	yajirusi = TriMeshs.get("yajirusi");
	yajirusi_tex = Textures.get("yajirusi");
	yaji_mate = Materials.get("default");
	point_material = Materials.get("pointMat");
	goal_mate = Materials.get("goal_mate");
	clear_mate = Materials.get("clear_mate");
	setStart();
	radius = 2;
	is_all_clear = false;
}

void CheckPoint::update()
{

	/*if (!is_all_clear) {
		if (isGoal()) {
			goalFn();
		}
	}*/
}

void CheckPoint::pushback(ci::Vec3f & _poin)
{
	points.push_back(_poin);
	is_clears.push_back(false);
	not_clear_index.push_back(not_clear_index.size());

}

void CheckPoint::setStart()
{
	if (not_clear_index.size() == 0) return;

	int _num;

	_num = randInt(0, not_clear_index.size());

	start_index = not_clear_index[_num];

	//not_clear_index.erase(not_clear_index.begin() + _num);

	dorone->transform.position = points[start_index];



	while (true)
	{
		int _goal = randInt(0, is_clears.size());
		if (start_index != _goal) {
			goal_index = _goal;
			return;
		}
	}

}

bool CheckPoint::isGoal()
{

	float r = (dorone->getRadius() + radius) *(dorone->getRadius() + radius);

	return dorone->transform.position.distanceSquared(points[goal_index]) < r;
}

void CheckPoint::goalFn()
{
	is_clears[start_index] = true;
	
	not_clear_index.erase(
		std::remove_if(not_clear_index.begin(), not_clear_index.end()
			, [&](int& i) { return i == start_index; })
		, not_clear_index.end());

	if (not_clear_index.size() == 0) {
		is_all_clear = true;
		goal_index = INT_MAX;
		return;
	}

	setStart();
	//dorone->onGoal();
}

bool CheckPoint::isAllClear()
{
	return is_all_clear;
}


void CheckPoint::draw()
{
	for (int i = 0; i < points.size(); i++) {
		point_material->apply();
		if (is_clears[i])clear_mate->apply();
		if (i == goal_index)goal_mate->apply();

		gl::drawSphere(points[i], 2);

	}
	if (!is_all_clear) {
		gl::pushMatrices();
		gl::translate(dorone->transform.position);
		gl::multModelView(ci::Matrix44f::createRotation(Vec3f::zAxis(),
			-points[goal_index] + dorone->transform.position,
			Vec3f::yAxis()));
		gl::translate(Vec3f::zAxis() * -8);

		yaji_mate->apply();
		yajirusi_tex->enableAndBind();
		gl::draw(*yajirusi);
		yajirusi_tex->disable();
		
		gl::popMatrices();

	}
}





