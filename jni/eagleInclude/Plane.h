#ifndef _PLANE_H_
#define _PLANE_H_
#include <GameObject.h>

class Plane:public GameObject{
private:
	Mesh planeMesh;
	Material mat;
	MeshRender meshRender;
public:
	Plane();
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
