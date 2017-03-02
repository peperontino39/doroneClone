#include "MaterialEdit.h"
#include "../../System/Interface/Interface.h"
#include "cinder/params/Params.h"
#include "cinder/Json.h"

using namespace ci;
using namespace ci::app;

MaterialEdit::MaterialEdit()
{
}

MaterialEdit::~MaterialEdit()
{
	c_Interface.pop("MaterialEdit");
}

void MaterialEdit::setup()
{
	ambient = Color::white();
	diffuse = Color::white();
	specular = Color::white();
	direction = Vec3f::one();
	light = new gl::Light(gl::Light::DIRECTIONAL, 0);
	// ŠÂ‹«Œõ‚ÌF
	light->setAmbient(ambient);
	// ŠgŽUŒõ‚ÌF
	light->setDiffuse(diffuse);
	// ‹¾–ÊŒõ‚ÌF
	light->setSpecular(specular);
	// ŒõŒ¹‚ÌŒü‚«
	light->setDirection(direction);

	light->enable();

	material = gl::Material(
		ColorA::black(),    // ŠÂ‹«Œõ‚ª“–‚½‚Á‚½Žž‚ÌF
		ColorA::white(),    // ŠgŽUŒõ‚ª“–‚½‚Á‚½Žž‚ÌF
		ColorA::white(),    // ‹¾–ÊŒõ‚ª“–‚½‚Á‚½Žž‚ÌF
		80.0f,                             // ‹¾–Ê”½ŽË‚Ì‰s‚³(’l‚ª‘å‚«‚¢‚Ù‚Ç‰s‚­‚È‚é)
		ColorA::black());
	c_Interface.create("MaterialEdit");
	auto interface = c_Interface.get("MaterialEdit");

	interface->addParam("ambient", &ambient).updateFn([&]() {
		light->setAmbient(ambient);
	}).group("light");
	interface->addParam("BHambient", &BHambient).updateFn([&]() {
		ambient = Color::gray(BHambient / 255.f);
		light->setAmbient(ambient);
	}).group("light").min(0).max(255);

	interface->addParam("diffuse", &diffuse).updateFn([&]() {
		light->setDiffuse(diffuse);
	}).group("light");
	interface->addParam("BHdiffuse", &BHdiffuse).updateFn([&]() {
		diffuse = Color::gray(BHdiffuse / 255.f);
		light->setDiffuse(diffuse);
	}).group("light").min(0).max(255);

	interface->addParam("specular", &specular).updateFn([&]() {
		light->setSpecular(specular);
	}).group("light");
	interface->addParam("BHspecular", &BHspecular).updateFn([&]() {
		specular = Color::gray(BHspecular / 255.f);
		light->setSpecular(specular);
	}).group("light").min(0).max(255);

	interface->addParam("direction", &direction).updateFn([&]() {
		light->setDirection(direction);
	}).group("light");

	interface->addParam<ColorA>("Ambient",
		std::bind(&gl::Material::setAmbient, &material, std::placeholders::_1),
		std::bind(&gl::Material::getAmbient, &material)).group("material");
	interface->addParam("BHAmbient", &BHAmbient).updateFn([&]() {
		material.setAmbient(Color::gray(BHAmbient / 255.f));
	}).group("material").min(0).max(255);

	interface->addParam<ColorA>("Diffuse",
		std::bind(&gl::Material::setDiffuse, &material, std::placeholders::_1),
		std::bind(&gl::Material::getDiffuse, &material)).group("material");
	interface->addParam("BHDiffuse", &BHDiffuse).updateFn([&]() {
		material.setDiffuse(Color::gray(BHDiffuse / 255.f));
	}).group("material").min(0).max(255);

	interface->addParam<ColorA>("Specular",
		std::bind(&gl::Material::setSpecular, &material, std::placeholders::_1),
		std::bind(&gl::Material::getSpecular, &material)).group("material");
	interface->addParam("BHSpecular", &BHSpecular).updateFn([&]() {
		material.setSpecular(Color::gray(BHSpecular / 255.f));
	}).group("material").min(0).max(255);

	interface->addParam<float>("Shininess",
		std::bind(&gl::Material::setShininess, &material, std::placeholders::_1),
		std::bind(&gl::Material::getShininess, &material)).group("material").step(0.1f);

	interface->addParam<ColorA>("Emission",
		std::bind(&gl::Material::setEmission, &material, std::placeholders::_1),
		std::bind(&gl::Material::getEmission, &material)).group("material");
	interface->addParam("BHEmission", &BHEmission).updateFn([&]() {
		material.setEmission(Color::gray(BHEmission / 255.f));
	}).group("material").min(0).max(255);

	interface->addParam<int>("Face",
		std::bind(&gl::Material::setFace, &material, std::placeholders::_1),
		std::bind(&gl::Material::getFace, &material)).group("material");
	interface->addSeparator();
	interface->addParam("MaterialName", &mat_name);
	interface->addButton("Save", std::bind(&MaterialEdit::save, this));
}

void MaterialEdit::update()
{
}

void MaterialEdit::draw()
{
	gl::drawVector(Vec3f::zero(), direction);

	gl::enable(GL_LIGHTING);
	gl::enable(GL_NORMALIZE);

	//gl::pushMatrices();
	//gl::rotate(Vec3f(app::getElapsedFrames(), getElapsedFrames(), 0));
	light->setDirection(direction);
	//gl::popMatrices();


	material.apply();

	gl::pushModelView();
	//gl::rotate(Vec3f(app::getElapsedFrames(), getElapsedFrames(), 0));
	gl::drawTorus(5, 1, 50, 50);

	gl::drawCube(Vec3f::zAxis() * 10, Vec3f::one());
	gl::drawSphere(Vec3f::zAxis()  * -10, .5f);
	gl::popModelView();

	gl::disable(GL_LIGHTING);
}

JsonTree coloToJson(std::string _key, ColorA& color) {
	JsonTree _color = JsonTree::makeObject(_key);
	_color.pushBack(JsonTree("", color.r));
	_color.pushBack(JsonTree("", color.g));
	_color.pushBack(JsonTree("", color.b));
	_color.pushBack(JsonTree("", color.a));
	return _color;
}


void MaterialEdit::save()
{
	if (mat_name == "")return;
	JsonTree json;
	JsonTree ambient = coloToJson("Ambient", material.getAmbient());
	JsonTree diffuse = coloToJson("Diffuse", material.getDiffuse());
	JsonTree specular = coloToJson("Specular", material.getSpecular());
	JsonTree shininess = JsonTree("Shininess", material.getShininess());
	JsonTree emission = coloToJson("Emission", material.getEmission());
	json.pushBack(ambient);
	json.pushBack(diffuse);
	json.pushBack(specular);
	json.pushBack(shininess);
	json.pushBack(emission);

	json.write("../assets/Material/" + mat_name + ".json");
}
