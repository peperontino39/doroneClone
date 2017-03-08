#include "Map.h"
#include "cinder/gl/gl.h"
#include "../../MyGameObject/MyArea/MyArea.h"
#include "cinder/Json.h"
#include "../../System/Utility/Utility.h"
#include "cinder/app/App.h"
#include "../../System/Input/Input.h"
#include "cinder/gl/Material.h"
#include "cinder/gl/Texture.h"
#include "cinder/Quaternion.h"
#include "../../AssetManager/TriMeshManager/TriMeshManager.h"
#include "../../AssetManager/TextureManager/TextureManager.h"
#include "../../AssetManager/MaterialManager/MaterialManager.h"
#include "../../MyGameObject/Dorone/Dorone.h"
#include "cinder/Ray.h"
#include "cinder/TriMesh.h"
#include "../../MyGameObject/CheckPoint/CheckPoint.h"

using namespace ci;
using namespace ci::app;

Map::Map(int _stage_num)
{
	stage_num = _stage_num;
}

void Map::setup()
{
	//stage_num = 3;
	JsonTree json(loadAsset("Stage/Stage" + std::to_string(stage_num) + ".json"));
	JsonTree stage_info = json.getChild("StageInfo");
	Vec3f pos = JtoVec3f(stage_info.getChild("Center"));
	Vec3f size = JtoVec3f(stage_info.getChild("StageSize"));

	JsonTree obs_info = json.getChild("obs_info");
	for (auto& obj : obs_info)
	{
		ObstacleDate obs_data;
		obs_data.transform.position = JtoVec3f(obj.getChild("position"));
		obs_data.transform.scale = JtoVec3f(obj.getChild("scale"));
		Vec3f rot = JtoVec3f(obj.getChild("rotate"));
		obs_data.transform.rotate = Quatf(Matrix44f::createRotation(ci::Vec3f(
			ci::toRadians(rot.x),
			ci::toRadians(rot.y),
			ci::toRadians(rot.z))));
		obs_data.mesh = TriMeshs.get(obj.getValueForKey<std::string>("mesh"));
		obs_data.material = Materials.get(obj.getValueForKey<std::string>("material"));
		obs_data.texture = Textures.get(obj.getValueForKey<std::string>("texture"));


		if (obj.getValueForKey<int>("isGround")) {
			grounds.push_back(obs_data);
		}
		else
		{
			obstacles.push_back(obs_data);
		}
	}
	auto points_json = json.getChild("Points");
	for (auto& obj : points_json)
	{
		check_point->pushback(JtoVec3f(obj));
	}

	
	my_area->setMyArea(pos, size);
}

void Map::update()
{

	Ray pray = Ray(onDorones->transform.position,
		Vec3f(0, -1000, 0));
	float leng = FLT_MAX;
	bool is_hit = false;

	for (auto& obj : grounds)
	{
		Matrix44f mat = obj.transform.getMultiMatrix();
		mat.invert();
		Ray _ray = pray;
		_ray.setOrigin(mat * pray.getOrigin());
		_ray.setDirection(mat.transformVec(pray.getDirection()));

		ci::AxisAlignedBox3f aabb = (*obj.mesh).calcBoundingBox();
		
		if (!aabb.intersects(_ray)) continue;

		ci::Vec3f pos[3];
		float inter_z = leng;
		for (size_t i = 0; i < (*obj.mesh).getNumTriangles(); i++)
		{
			(*obj.mesh).getTriangleVertices(i, &pos[0], &pos[1], &pos[2]);
			if (_ray.calcTriangleIntersection(pos[0], pos[1], pos[2], &inter_z)) {
				if (inter_z < leng) {
					leng = inter_z;
					is_hit = true;
				}
			}
		}
	}
	if (is_hit) {
		Vec3f colc_pos = pray.calcPosition(leng);
		if (colc_pos.y + 3 >= onDorones->transform.position.y) {
			onDorones->transform.position.y = colc_pos.y + 3;
			onGroundFn();
		}
	}
}

bool AABBtoVec3f(Vec3f& min, Vec3f& max, Vec3f _pos) {
	if (min.x < _pos.x &&  _pos.x < max.x)
		if (min.y < _pos.y &&  _pos.y < max.y)
			if (min.z < _pos.z &&  _pos.z < max.z)
				return true;
	return false;
}

void Map::draw()
{

	for (auto& obs : obstacles) {
		ci::gl::pushMatrices();
		ci::gl::multModelView(obs.transform.getMultiMatrix());
		obs.material->apply();
		obs.texture->enableAndBind();
		ci::gl::draw(*obs.mesh);
		obs.texture->disable();

		ci::gl::popMatrices();
	}
	for (auto& obs : grounds) {
		ci::gl::pushMatrices();
		ci::gl::multModelView(obs.transform.getMultiMatrix());
		obs.material->apply();
		obs.texture->enableAndBind();
		ci::gl::draw(*obs.mesh);
		obs.texture->disable();


		
		std::vector<Vec3f> a = obs.mesh->getVertices();

		ci::Vec3f pos[3];
		for (size_t i = 0; i < (*obs.mesh).getNumTriangles(); i++)
		{
			(*obs.mesh).getTriangleVertices(i, &pos[0], &pos[1], &pos[2]);
		}
		

		ci::gl::popMatrices();

	}
	

	/*if (isHitTriMeshToSphere()) {
		gl::drawStrokedCube(onDorones->transform.position, Vec3f::one() * 5);
	}*/




}

bool Map::istrigr()
{
	return c_Input.getKeyPush(ci::app::KeyEvent::KEY_2);
}




bool Map::isHitTriMeshToSphere()
{

	float r = onDorones->getRadius();
	float r2 = r*r;
	for (auto& obs : obstacles)
	{
		auto mesh = obs.mesh;

		AxisAlignedBox3f aabb = mesh->calcBoundingBox(obs.transform.getMultiMatrix());
		Vec3f min = aabb.getMin() - Vec3f::one() * r;
		Vec3f max = aabb.getMax() + Vec3f::one() * r;
		
		if (!AABBtoVec3f(min, max, onDorones->transform.position)) {
			continue;
		}

		std::vector<Vec3f> vertices = mesh->getVertices();
		for (auto& ver : vertices)
		{
			ver = obs.transform.getMultiMatrix() * ver;
		}


		auto index = mesh->getIndices();
		for (size_t i = 0; i < mesh->getNumTriangles(); i++)
		{
			Vec3f point[3];
			point[0] = vertices[index[i * 3]];
			point[1] = vertices[index[i * 3 + 1]];
			point[2] = vertices[index[i * 3 + 2]];

			Vec3f v0 = point[1] - point[2];
			Vec3f v1 = point[0] - point[1];
			Vec3f v2 = point[0] - point[2];

			//‹——£
			Vec3f cross = v1.cross(v2);
			cross.normalize();
			Vec3f vecT = onDorones->transform.position - point[0];
			float ln = cross.dot(vecT);

			//‹——£‚ª“–‚½‚Á‚Ä‚È‚©‚Á‚½‚ç >
			if (std::abs(ln) > r) {
				continue;
			}

			//•Ó
			float len0 = v0.length();
			float len1 = v1.length();
			float len2 = v2.length();

			Vec3f v0n = v0 / len0;
			Vec3f v1n = v1 / len1;
			Vec3f v2n = v2 / len2;

			//Še•Ó‚ÉÅ‚à‹ß‚¢“_
			
			Vec3f h0 = point[2] + v0n *
				std::min(std::max(v0n.dot((onDorones->transform.position - point[2])), 0.f), len0);
			Vec3f h1 = point[1] + v1n *
				std::min(std::max(v1n.dot((onDorones->transform.position - point[1])), 0.f), len1);
			Vec3f h2 = point[2] + v2n *
				std::min(std::max(v2n.dot((onDorones->transform.position - point[2])), 0.f), len2);

			if (h0.distanceSquared(onDorones->transform.position) < r2)return true;
			if (h1.distanceSquared(onDorones->transform.position) < r2)return true;
			if (h2.distanceSquared(onDorones->transform.position) < r2)return true;

			Vec3f p = onDorones->transform.position - cross * ln;

			
			bool isPoint = true;

			Vec3f v3 = point[0] - p;
			Vec3f v4 = point[1] - p;
			Vec3f v5 = point[2] - p;

			
			Vec3f cp;

			cp = v3.cross(v4);
			if (cross.dot(cp) < 0) isPoint = false;
			cp = v4.cross(v5);
			
			if (cross.dot(cp) < 0) isPoint = false;
			cp = v5.cross(v3);
			
			if (cross.dot(cp) < 0) isPoint = false;

			if (isPoint) {
				return true;
			}
		}

		//’¸“_
		/*for (auto& ver : vertices)
		{
			if (ver.distanceSquared(onDorones->transform.position) < r2) {
				return true;
			}
		}*/

	}
	return false;
}


