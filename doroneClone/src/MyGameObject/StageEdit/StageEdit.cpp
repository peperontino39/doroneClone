#include "StageEdit.h"
#include "cinder/gl/gl.h"
#include "../../System/Interface/Interface.h"
#include "cinder/params/Params.h"
#include "cinder/Json.h"
#include "cinder/app/App.h"
#include "../../AssetManager/TriMeshManager/TriMeshManager.h"
#include "../../AssetManager/TextureManager/TextureManager.h"
#include "../../AssetManager/MaterialManager/MaterialManager.h"
#include "cinder/gl/Material.h"
#include "../../System/Input/Input.h"
#include "cinder/TriMesh.h"
#include "cinder/Sphere.h"
#include "../../System/Utility/Utility.h"

using namespace ci;
using namespace ci::app;


StageEdit::StageEdit()
{
	c_Interface.create("StageEdit");
	mInterface = c_Interface.get("StageEdit");

	transform.scale = Vec3f::one() * 100;
	create_point = false;
	ereas_point = false;
	stage_num = 1;
	point_material = Materials.get("pointMat");
	point_upvec = Vec3f::yAxis() * 3;
	radius = 2;

	mInterface->addParam("stageCenter", &transform.position);
	mInterface->addParam("stageScale", &transform.scale);
	mInterface->addParam("stage_num", &stage_num).updateFn([&]() {load(); });
	mInterface->addButton("load", std::bind(&StageEdit::load, this));
	mInterface->addButton("save", std::bind(&StageEdit::save, this));
	mInterface->addButton("create", std::bind(&StageEdit::create, this));
	mInterface->addButton("clear", std::bind(&StageEdit::clear, this));
	mInterface->addButton("erase", std::bind(&StageEdit::erase, this));
	mInterface->addParam("PointCreate", &create_point);
	mInterface->addParam("PointEreas", &ereas_point);


	mInterface->addSeparator();

	load();

}

StageEdit::~StageEdit()
{
	c_Interface.pop("StageEdit");
}

void StageEdit::update()
{
}

void StageEdit::draw()
{
	for (auto& obj : obstacles)
	{
		Matrix44f mat;
		mat *= Matrix44f::createTranslation(obj.position);
		mat *= ci::Matrix44f::createRotation(ci::Vec3f(
			ci::toRadians(obj.rotate.x),
			ci::toRadians(obj.rotate.y),
			ci::toRadians(obj.rotate.z)));
		mat *= Matrix44f::createScale(obj.scale);

		gl::pushModelView();
		gl::multModelView(mat);

		obj.material->apply();
		obj.texture->enableAndBind();
		gl::draw(*(obj.mesh));

		gl::popModelView();

		obj.texture->disable();

	}


	point_material->apply();
	for (auto& pot : points)
	{
		gl::drawSphere(pot, radius);
	}
	if (select_object != nullptr) {
		Matrix44f mat;
		mat *= Matrix44f::createTranslation(select_object->position);
		mat *= ci::Matrix44f::createRotation(ci::Vec3f(
			ci::toRadians(select_object->rotate.x),
			ci::toRadians(select_object->rotate.y),
			ci::toRadians(select_object->rotate.z)));
		mat *= Matrix44f::createScale(select_object->scale);
		gl::pushModelView();
		gl::multModelView(mat);
		gl::drawCoordinateFrame();
		gl::popModelView();
	}
	gl::drawStrokedCube(transform.position, transform.scale);
	if (create_point) {
		Ray pray = rayFn();
		float leng = FLT_MAX;

		for (auto& obj : obstacles)
		{
			Matrix44f mat;
			mat *= Matrix44f::createTranslation(obj.position);
			mat *= ci::Matrix44f::createRotation(ci::Vec3f(
				ci::toRadians(obj.rotate.x),
				ci::toRadians(obj.rotate.y),
				ci::toRadians(obj.rotate.z)));
			mat *= Matrix44f::createScale(obj.scale);
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
					}
				}
			}
		}
		Vec3f colc_pos = pray.calcPosition(leng) + point_upvec;
		point_material->apply();
		gl::drawSphere(colc_pos, radius);

	}

}

void StageEdit::mouseDown()
{
	if (c_Input.getMousePush(MouseEvent::LEFT_DOWN)) {

		Ray pray = rayFn();
		float leng = FLT_MAX;
		ObstacleDate* hitobj = nullptr;

		for (auto& obj : obstacles)
		{
			Matrix44f mat;
			mat *= Matrix44f::createTranslation(obj.position);
			mat *= ci::Matrix44f::createRotation(ci::Vec3f(
				ci::toRadians(obj.rotate.x),
				ci::toRadians(obj.rotate.y),
				ci::toRadians(obj.rotate.z)));
			mat *= Matrix44f::createScale(obj.scale);
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
						hitobj = &obj;

					}
				}
			}
		}
		if (hitobj != nullptr) {
			if (create_point) {
				points.push_back(pray.calcPosition(leng) + point_upvec);
				create_point = false;
			}
		}
		setSelectObject(hitobj);
	}
	if (ereas_point) {
		Ray pray = rayFn();
		float leng_max = FLT_MAX;
		auto hit_poi = points.end();
		for (auto pot = points.begin(); pot != points.end(); pot++)
		{
			float pot_z;
			if (ci::Sphere(*pot, radius).intersect(pray, &pot_z)) {
				if (leng_max > pot_z) {
					leng_max = pot_z;
					hit_poi = pot;

				}
			}
		}
		if (hit_poi != points.end()) {
			points.erase(hit_poi);
			ereas_point = false;
		}
	}
}

void StageEdit::load()
{
	clear();
	points.clear();
	JsonTree  json(loadAsset("Stage/Stage" + std::to_string(stage_num) + ".json"));

	JsonTree  stage = json.getChild("StageInfo");
	transform.position = JtoVec3f(stage.getChild("Center"));
	transform.scale = JtoVec3f(stage.getChild("StageSize"));

	auto obs_infos = json.getChild("obs_info");
	for (auto obj = obs_infos.begin(); obj != obs_infos.end(); obj++)
	{
		ObstacleDate obs;
		obs.position = JtoVec3f(obj->getChild("position"));
		obs.rotate = JtoVec3f(obj->getChild("rotate"));
		obs.scale = JtoVec3f(obj->getChild("scale"));

		obs.mesh_name = obj->getValueForKey<std::string>("mesh");
		obs.mesh = TriMeshs.get(obs.mesh_name);

		obs.material_name = obj->getValueForKey<std::string>("material");
		obs.material = Materials.get(obs.material_name);

		if (obj->hasChild("texture")) {
			obs.texture_name = obj->getValueForKey<std::string>("texture");
			obs.texture = Textures.get(obs.texture_name);
		}
		obs.is_ground = (bool)obj->getValueForKey<int>("isGround");

		obstacles.push_back(obs);
	}

	auto point_json = json.getChild("Points");
	for (auto& poi : point_json)
	{
		points.push_back(JtoVec3f(poi));
	}

}

void StageEdit::save()
{
	JsonTree json;
	JsonTree _stage = JsonTree::makeArray("StageInfo");
	JsonTree center = JsonTree::makeArray("Center");
	center.pushBack(JsonTree("", transform.position.x));
	center.pushBack(JsonTree("", transform.position.y));
	center.pushBack(JsonTree("", transform.position.z));
	_stage.pushBack(center);
	JsonTree _size = JsonTree::makeArray("StageSize");
	_size.pushBack(JsonTree("", transform.scale.x));
	_size.pushBack(JsonTree("", transform.scale.y));
	_size.pushBack(JsonTree("", transform.scale.z));
	_stage.pushBack(_size);

	json.pushBack(_stage);

	JsonTree obs_info = JsonTree::makeArray("obs_info");

	for (auto& obj : obstacles)
	{
		JsonTree objectjson;
		JsonTree pos = JsonTree::makeArray("position");
		pos.pushBack(JsonTree("", obj.position.x));
		pos.pushBack(JsonTree("", obj.position.y));
		pos.pushBack(JsonTree("", obj.position.z));
		JsonTree rot = JsonTree::makeArray("rotate");
		rot.pushBack(JsonTree("", obj.rotate.x));
		rot.pushBack(JsonTree("", obj.rotate.y));
		rot.pushBack(JsonTree("", obj.rotate.z));
		JsonTree scal = JsonTree::makeArray("scale");
		scal.pushBack(JsonTree("", obj.scale.x));
		scal.pushBack(JsonTree("", obj.scale.y));
		scal.pushBack(JsonTree("", obj.scale.z));
		if (obj.mesh != nullptr) {
			objectjson.pushBack(JsonTree("mesh", obj.mesh_name));
		}
		if (obj.material != nullptr) {
			objectjson.pushBack(JsonTree("material", obj.material_name));
		}
		if (obj.texture != nullptr) {
			objectjson.pushBack(JsonTree("texture", obj.texture_name));
		}
		objectjson.pushBack(JsonTree("isGround", obj.is_ground));

		objectjson.pushBack(pos);
		objectjson.pushBack(rot);
		objectjson.pushBack(scal);

		obs_info.pushBack(objectjson);
	}
	json.pushBack(obs_info);

	JsonTree points_json = JsonTree::makeArray("Points");
	for (auto& poi : points)
	{
		JsonTree pos;
		pos.pushBack(JsonTree("", poi.x));
		pos.pushBack(JsonTree("", poi.y));
		pos.pushBack(JsonTree("", poi.z));
		points_json.pushBack(pos);
	}

	json.pushBack(points_json);



	console() << json << std::endl;

	json.write("../assets/Stage/Stage" + std::to_string(stage_num) + ".json");
}


void StageEdit::create()
{

	ObstacleDate obs;
	obs.position = Vec3f::zero();
	obs.rotate = Vec3f::zero();
	obs.scale = Vec3f::one();
	obs.mesh_name = "default";
	obs.mesh = TriMeshs.get(obs.mesh_name);
	obs.material_name = "default";
	obs.material = Materials.get(obs.material_name);
	obs.texture_name = "default";
	obs.texture = Textures.get(obs.texture_name);
	obs.is_ground = false;

	obstacles.push_back(obs);

	auto& it = obstacles.back();
	setSelectObject(&it);

}

void StageEdit::clear()
{
	obstacles.clear();
	setSelectObject(nullptr);
}

void StageEdit::erase()
{

	for (auto obj = obstacles.begin(); obj != obstacles.end(); obj++)
	{
		if (select_object == &(*obj)) {
			obstacles.erase(obj);
			break;
		}
	}
	setSelectObject(nullptr);
}

void StageEdit::setSelectObject(ObstacleDate * _select)
{

	if (select_object != nullptr) {
		mInterface->removeParam("position");
		mInterface->removeParam("rotate");
		mInterface->removeParam("scale");
		mInterface->removeParam("mesh_name");
		mInterface->removeParam("material_name");
		mInterface->removeParam("texture_name");
		mInterface->removeParam("isGround");

	}

	select_object = _select;
	if (_select != nullptr) {

		mInterface->addParam("position", &select_object->position);
		mInterface->addParam("rotate", &select_object->rotate);
		mInterface->addParam("scale", &select_object->scale);
		mInterface->addParam("mesh_name", &select_object->mesh_name).updateFn([&]() {
			if (TriMeshs.isHave(select_object->mesh_name)) {
				select_object->mesh = TriMeshs.get(select_object->mesh_name);
			}
			else
			{
				select_object->mesh_name = "default";
				select_object->mesh = TriMeshs.get(select_object->mesh_name);
			}
		}
		);
		mInterface->addParam("material_name", &select_object->material_name).updateFn([&]() {
			if (Materials.isHave(select_object->material_name)) {
				select_object->material = Materials.get(select_object->material_name);
			}
			else
			{
				select_object->material_name = "default";
				select_object->material = Materials.get(select_object->material_name);
			}
		}
		);
		mInterface->addParam("texture_name", &select_object->texture_name).updateFn([&]() {

			if (Textures.isHave(select_object->texture_name)) {
				select_object->texture = Textures.get(select_object->texture_name);
			}
			else
			{
				select_object->texture_name = "default";
				select_object->texture = Textures.get(select_object->texture_name);
			}
		}
		);
		mInterface->addParam("isGround", &select_object->is_ground);
	}


}
