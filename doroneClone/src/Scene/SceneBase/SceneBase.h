#pragma once
#include <list>
#include <memory>
#include <functional>

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectRef;



class SceneBase
{
public:
	virtual void onCreate();

	virtual void setup();

	virtual void update();
	
	virtual void cameraDrawBegin();
	virtual void lightDrawBegin();
	virtual void draw();
	virtual void cameraDrawEnd();
	virtual void lightDrawEnd();
	virtual void drawUI();

	virtual void shutdown();

	virtual void mouseDown();
	virtual void mouseUp();
	virtual void mouseWheel();
	virtual void mouseMove();
	virtual void mouseDrag();

	virtual void keyDown();
	virtual void keyUp();

	virtual void resize();

	std::function<SceneBase*()> nextScene = [&]() {return nullptr; };
protected:

	void create(GameObject* obj);
	template<class T> 
	T* Instantiate(T*);
	std::list<GameObject*> gameObjects;

};

template<class T>
T * SceneBase::Instantiate(T * obj)
{
	gameObjects.push_back(obj);
	return obj;
}
