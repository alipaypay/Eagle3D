#ifndef FORWARD_AMBIENT_H
#define FORWARD_AMBIENT_H
#include "Shader.h"
class ForwardAmbient : public Shader{
private:
	static  ForwardAmbient* Instance;
	ForwardAmbient();
public:

	void UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam);
	static ForwardAmbient* GetInstance();

};

#endif
