#pragma once
#include "../../System/CinderFwd.h"
#include "../../GameObject/GameObject.h"
#include "cinder/Camera.h" 

class CameraWork : public GameObject
{
public:
	void setup();
	void cameraDrawBegin();
	void update();

	void draw();
	void cameraDrawEnd();
	void resize();
	
	void setTransfome(Transform&, float up = 0.5);
	void setTransfomeE(Transform&,float, float up = 0.5);

	void setCenterT(ci::Vec3f);
	void setDirectionT(ci::Vec3f);
	void setLengthT(float);

	void setCenter(ci::Vec3f);
	void setDirection(ci::Vec3f);
	void setLength(float);

	void setCenterE(ci::Vec3f,float);
	void setDirectionE(ci::Vec3f, float);
	void setLengthE(float,float);

	
private:

	ci::CameraPersp camera;

	ci::Vec3f center;
	ci::Vec3f direction;
	ci::Vec3f terget_direction;
	ci::Vec3f terget_center;
	float length;

	bool is_move_terget = true;

};
