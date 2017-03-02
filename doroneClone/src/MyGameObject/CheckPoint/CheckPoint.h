#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"


class Dorone;
class Map;

class CheckPoint : public GameObject
{
public:
	void draw(); 
	void setup();
	void update();

	Dorone * dorone;
	Map* map;

	void pushback(ci::Vec3f&);
	void setStart();
	bool isGoal();
	void goalFn();
	bool isAllClear();


private:
	std::vector<ci::Vec3f> points;
	std::vector<bool> is_clears;
	std::vector<int>not_clear_index;

	MaterialRef point_material;
	MaterialRef goal_mate;
	MaterialRef clear_mate;


	int start_index;
	int goal_index;
	float radius;
	bool is_all_clear;

	TriMeshRef yajirusi;
	ci::gl::TextureRef yajirusi_tex;
	MaterialRef yaji_mate;

	
};

