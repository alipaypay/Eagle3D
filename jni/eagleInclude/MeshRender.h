#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include "Component.h"
#include "Mesh.h"
#include "Material.h"
class MeshRender : public Component{

private:
	Mesh mesh;
	Material material;
	Shader *currShader;
public:
	MeshRender(Mesh mesh,Material mat);
	virtual void Render(Shader* shader,RenderOfCamera* renderOfCam);
	virtual void Update(float delta);
	Shader* GetCurrentShader();
	virtual void Pause();
	virtual void Resume();
	virtual void ApplicationQuit();
};

#endif
