#include "Dorone.h"
#include "../../AssetManager/TriMeshManager/TriMeshManager.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/CinderMath.h"
#include "../../System/Coroutine/Coroutine.h"
#include "../../System/Input/Input.h"
#include "../../AssetManager/MaterialManager/MaterialManager.h"
#include "cinder/gl/Material.h"
#include "../CameraWork/CameraWork.h"
#include "../../MyGameObject/DoroneMemory/DoroneMemory.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;

Dorone::Dorone()
{
	transform.position += Vec3f::yAxis() * 5;
	radius = 3;
	body = TriMeshs.get("drone");
	wing = TriMeshs.get("droneWing");
	vec = Vec3f::zero();
	tergetVec = Vec3f::zero();
	matelial = Materials.get("dorone");

	matelial->setDiffuse(ColorA(
		randFloat(0.f,1.f), 
		randFloat(0.f, 1.f),
		randFloat(0.f, 1.f),
		1.f));
	transform.position.y = 4;
	/*c_Coroutine(3, [&]() {
		transform.position.x += 10;
	});*/
	is_move = false;
	is_draw = true;
}

void Dorone::setup()
{

}

void Dorone::update()
{
	
	if (is_move) {
		moveFn();

		DroneOneFrame oneFra;
		oneFra.pos = transform.position;
		oneFra.rot = transform.rotate;
		memory.push_back(oneFra);

	}
}

void Dorone::draw()
{
	if (!is_draw)return;
	matelial->apply();
	//gl::drawSphere(transform.position, radius);
	gl::pushMatrices();
	gl::translate(Vec3f::yAxis() * -3);
	gl::multModelView(transform.getMultiMatrix());
	
	float size = 0.5f;
	gl::scale(size, size, size);

	gl::draw(*body);

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

	gl::popMatrices();
}

void Dorone::keyDown()
{

}

void Dorone::mouseDown()
{
	/*dorone_memory->pushBack(memory, *matelial);
	dorone_memory->reset();
	memory.clear();*/
}

void Dorone::onGround()
{
	vec.y = 0;
}

float Dorone::getRadius()
{
	return radius;
}

void Dorone::onGoal()
{
	tergetVec = Vec3f::zero();
	vec = Vec3f::zero();
	dorone_memory->pushBack(memory, *matelial);
	matelial->setDiffuse(ColorA(
		randFloat(0.f, 1.f),
		randFloat(0.f, 1.f),
		randFloat(0.f, 1.f),
		1.f));
	dorone_memory->reset();
	memory.clear();
	setIsMove(false);
}

void Dorone::setIsMove(bool _move)
{
	is_move = _move;
}

void Dorone::setIsDraw(bool _draw)
{
	is_draw = _draw;
}

void Dorone::setMemoryTransform(int _index)
{
	transform.position = memory[_index].pos;
	transform.rotate  = memory[_index].rot;

}

void Dorone::memoryClear()
{
	memory.clear();
}

void Dorone::hitFn()
{
	tergetVec = Vec3f::zero();
	vec = Vec3f::zero();
}

void Dorone::moveFn()
{
	float rot = 0;
	float rot_speed = 0.1f;
	if (c_Input.getKeyPress(KeyEvent::KEY_j)) {
		rot += rot_speed;
	}
	if (c_Input.getKeyPress(KeyEvent::KEY_l)) {
		rot -= rot_speed;
	}
	transform.rotate *= Quatf(Vec3f::yAxis(), rot);

	float move_speed = 0.5f;
	Vec2f move_vec = Vec2f::zero();
	if (c_Input.getKeyPress(KeyEvent::KEY_0)) {
		transform.position.y++;
	}
	if (c_Input.getKeyPress(KeyEvent::KEY_p)) {
		transform.position.y--;
	}

	if (c_Input.getKeyPress(KeyEvent::KEY_w)) {
		move_vec.y += move_speed;
	}
	if (c_Input.getKeyPress(KeyEvent::KEY_s)) {
		move_vec.y -= move_speed;
	}
	if (c_Input.getKeyPress(KeyEvent::KEY_a)) {
		move_vec.x += move_speed;
	}
	if (c_Input.getKeyPress(KeyEvent::KEY_d)) {
		move_vec.x -= move_speed;
	}
	move_vec = (Vec3f(move_vec.x, 0, move_vec.y) * transform.rotate).xz();
	move(move_vec.x, move_vec.y);

	Vec3f temp = ci::lerp(vec, tergetVec, 0.01f);
	vec.x = temp.x;
	vec.z = temp.z;
	vec.y -= 0.01f;

	transform.position += vec;

}

void Dorone::move(float x, float z)
{
	tergetVec.x = x;
	tergetVec.z = z;
}

void Dorone::up(float)
{
}

void Dorone::turning(float)
{
}
