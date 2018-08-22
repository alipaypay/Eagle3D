#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"
#include <vector>
#include "Transform.h"
#include "Shader.h"
#include "RenderOfCamera.h"
using namespace std;
class GameObject{
private:
	vector<GameObject*> childrenList;
	vector<GameObject*>::iterator removeResult;

	vector<Component*> components;

	Transform* transform;
public:
	GameObject();
	~GameObject();
	virtual void Update(float delta);
	virtual void Pause();
	virtual void Resume();
	virtual void ApplicationQuit();
	virtual void Render(Shader* shader,RenderOfCamera* renderOfCam);
	virtual void AddChild(GameObject* child);
	virtual void AddToRenderOfCamera(RenderOfCamera* renderOfCam);
	virtual void RemoveChildAll();
	virtual GameObject* AddComponent(Component* component);
	virtual Transform* GetTransform();
};
#endif
