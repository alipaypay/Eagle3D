#ifndef FORWARD_SPOT_H
#define FORWARD_SPOT_H

#include "Shader.h"
#include "SpotLight.h"
class ForwardSpot :public Shader{
private:
	static  ForwardSpot* Instance;
	ForwardSpot();
public:

	void UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam);
	static ForwardSpot* GetInstance();

};
#endif
