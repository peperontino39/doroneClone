#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/gl/Light.h"
#include "cinder/gl/Material.h"

class MaterialEdit : public GameObject
{
public:
	MaterialEdit();
	~MaterialEdit();

	void setup();
	void update();
	void draw();

private:
	ci::gl::Light* light;
	ci::Color ambient;
	ci::Color diffuse;
	ci::Color specular;
	ci::Vec3f direction;
	float BHambient = 0;
	float BHdiffuse = 0;
	float BHspecular = 0;


	ci::gl::Material material;
	float BHAmbient = 0;
	float BHDiffuse = 0;
	float BHSpecular = 0;
	float BHEmission = 0;

	std::string mat_name;

	void save();

};