#include "DoroneMemory.h"
#include "../../AssetManager/TriMeshManager/TriMeshManager.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"


using namespace ci;
using namespace ci::app;

DoroneMemory::DoroneMemory()
{
	count = 0;
	drone = TriMeshs.get("drone");
	wing = TriMeshs.get("droneWing");
}

void DoroneMemory::update()
{


}

void DoroneMemory::draw()
{
	for (auto& dro : memorys)
	{
		if (dro.ismove) {
			ci::gl::pushModelView();
			ci::Matrix44f _mat;
			_mat = ci::Matrix44f::createTranslation(dro.transfomes[count].pos);
			_mat = _mat * dro.transfomes[count].rot;
			ci::gl::multModelView(_mat);
			dro.mat.apply();

			ci::gl::draw(*drone);
			float rotateSpeed = 60 * 20;

			gl::pushMatrices();
			gl::translate(Vec3f(5, 9, 5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			gl::pushMatrices();
			gl::translate(Vec3f(5, 9, -5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			gl::pushMatrices();
			gl::translate(Vec3f(-5, 9, 5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			gl::pushMatrices();
			gl::translate(Vec3f(-5, 9, -5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			ci::gl::popModelView();
		}
		else
		{
			ci::gl::pushModelView();
			ci::Matrix44f _mat;
			_mat = ci::Matrix44f::createTranslation(dro.transfomes.back().pos);
			_mat = _mat * dro.transfomes.back().rot;
			ci::gl::multModelView(_mat);
			dro.mat.apply();

			ci::gl::draw(*drone);
			float rotateSpeed = 60 * 20;

			gl::pushMatrices();
			gl::translate(Vec3f(5, 9, 5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			gl::pushMatrices();
			gl::translate(Vec3f(5, 9, -5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			gl::pushMatrices();
			gl::translate(Vec3f(-5, 9, 5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			gl::pushMatrices();
			gl::translate(Vec3f(-5, 9, -5));
			gl::rotate(Vec3f(0, getElapsedSeconds() * rotateSpeed, 0));
			gl::draw(*wing);
			gl::popMatrices();

			ci::gl::popModelView();
		}
	}
}



void DoroneMemory::pushBack(std::vector<DroneOneFrame>& _trans, ci::gl::Material & _mat)
{
	OneDorone one_dro;
	for (auto& it : _trans)
	{
		one_dro.transfomes.push_back(it);
	}
	one_dro.mat = _mat;
	memorys.push_back(one_dro);
	if (_trans.size() > max_count)
		max_count = _trans.size();
}

void DoroneMemory::reset()
{
	count = 0;
	for (auto& dro : memorys)
	{

		dro.ismove = true;
	}
}

bool DoroneMemory::ishit(ci::Vec3f _pos, float r)
{
	for (auto& dro : memorys)
	{
		if (count >= dro.transfomes.size())continue;
		if (_pos.distanceSquared(dro.transfomes[count].pos) < r*r) {
			return true;
		}
	}
	
	return false;
}

void DoroneMemory::coundAdd(int _add)
{
	count += _add;
	count = std::max(0, count);
	for (auto& dro : memorys)
	{
		if (dro.transfomes.size() - 1 < count)
		{
			dro.ismove = false;
		}
		else {
			dro.ismove = true;
		}
	}
}

int DoroneMemory::getCount()
{
	return count;
}

void DoroneMemory::setCount(int _con)
{
	count = _con;
	for (auto& dro : memorys)
	{
		if (dro.transfomes.size() - 1 < count)
		{
			dro.ismove = false;
		}
		else {
			dro.ismove = true;
		}
	}
}

int DoroneMemory::maxCount()
{
	return max_count;
}
