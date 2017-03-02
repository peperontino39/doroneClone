#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include<list>

class StageEdit : public GameObject
{
public:
	StageEdit();
	~StageEdit();
	void update();
	void draw();

	void mouseDown();

	std::function<ci::Ray()> rayFn;

private:

	struct ObstacleDate
	{
		ci::Vec3f position;
		ci::Vec3f rotate;
		ci::Vec3f scale;
		std::string mesh_name;
		TriMeshRef mesh = nullptr;
		std::string material_name;
		MaterialRef material = nullptr;
		std::string texture_name;
		ci::gl::TextureRef texture = nullptr;
		bool is_ground;

	};

	void load();
	void save();
	void create();
	void clear();
	void erase();
	void setSelectObject(ObstacleDate*);
	

	int stage_num;
	std::list<ObstacleDate> obstacles;
	ObstacleDate* select_object;
	ci::params::InterfaceGlRef mInterface;
	ci::Vec3f point_upvec;
	bool create_point;
	bool ereas_point;
	float radius;

	MaterialRef point_material;

	std::list<ci::Vec3f> points;

};



