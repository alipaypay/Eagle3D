#ifndef COMPONENT_H
#define COMPONENT_H

#include "Transform.h"
#include "Shader.h"
class GameObject;
class Component{
private:
	GameObject *parent;
public:
	Component();
	virtual void Render(Shader* shader,RenderOfCamera* renderOfCam);
	virtual void Update(float delta);
	virtual void AddToRenderOfCamera(RenderOfCamera* renderOfCam);
	virtual Transform* GetTransform();
	virtual void SetParent(GameObject* parent);
	virtual	void Pause();
	virtual	void Resume();
	virtual void Render();
	virtual	void ApplicationQuit();
};
#endif
