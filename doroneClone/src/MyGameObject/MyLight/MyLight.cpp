#include "MyLight.h"
#include "cinder/gl/Light.h"



MyLight::MyLight()
{
	ci::Color ambient = ci::Color::white();
	ci::Color diffuse = ci::Color::white();
	ci::Color specular = ci::Color::white();
	direction.x = 0.6f;
	direction.y = 0.8f;
	direction.z = 1.f;

	light = new ci::gl::Light(ci::gl::Light::DIRECTIONAL, 0);
	// 環境光の色
	light->setAmbient(ambient);
	// 拡散光の色
	light->setDiffuse(diffuse);
	// 鏡面光の色
	light->setSpecular(specular);
	// 光源の向き
	light->setDirection(direction);

	light->enable();
}

MyLight ::~MyLight()
{
	delete light;
}

void MyLight::lightDrawBegin()
{
	ci::gl::enable(GL_LIGHTING);
	ci::gl::enable(GL_NORMALIZE);

	light->setDirection(direction);


}

void MyLight::lightDrawEnd()
{
	ci::gl::disable(GL_LIGHTING);
}
