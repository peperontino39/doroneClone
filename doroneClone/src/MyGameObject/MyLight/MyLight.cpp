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
	// ŠÂ‹«Œõ‚ÌF
	light->setAmbient(ambient);
	// ŠgŽUŒõ‚ÌF
	light->setDiffuse(diffuse);
	// ‹¾–ÊŒõ‚ÌF
	light->setSpecular(specular);
	// ŒõŒ¹‚ÌŒü‚«
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
