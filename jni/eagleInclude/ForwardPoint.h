#ifndef FORWARD_POINT_H
#define FORWARD_POINT_H

#include "Shader.h"
#include "PointLight.h"
class ForwardPoint :public Shader{
private:
	static  ForwardPoint* Instance;
	ForwardPoint();
public:

	void UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam);
	static ForwardPoint* GetInstance();

};
#endif
