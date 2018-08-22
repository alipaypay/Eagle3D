#ifndef FORWARD_DIRECTIONAL_H
#define FORWARD_DIRECTIONAL_H

#include "Shader.h"
#include "DirectionalLight.h"
class ForwardDirectional :public Shader{
private:
	static  ForwardDirectional* Instance;
	ForwardDirectional();
public:

	void UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam);
	static ForwardDirectional* GetInstance();

};
#endif
