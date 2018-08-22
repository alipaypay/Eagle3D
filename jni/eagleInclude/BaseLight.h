#ifndef BASE_LIGHT
#define BASE_LIGHT

#include "Component.h"
#include "Vector3.h"

class BaseLight : public Component{
private:
	Shader* shader;

public:
	BaseLight(Vector3 color,float intensity);
	BaseLight();
	BaseLight& operator = (const BaseLight &rBaseLight);
	Vector3 Color;
	float Intensity;
	virtual void AddToRenderOfCamera(RenderOfCamera* renderOfCam);
	void SetShader(Shader* shader);
	Shader* GetShader();
	virtual	void Pause();
	virtual	void Resume();
	virtual	void ApplicationQuit();
};

#endif
