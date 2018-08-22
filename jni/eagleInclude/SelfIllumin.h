#ifndef _SELF_ILLUMIN_
#define _SELF_ILLUMIN_
#include <Shader.h>
#include <Vector3.h>
#include <RenderOfCamera.h>
class SelfIllumin : public Shader{
private:
	static  SelfIllumin* Instance;
	SelfIllumin();
	Vector3 illuminIntensity;
public:

	void UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam);
	static SelfIllumin* GetInstance();
	void SetSelfIlluminIntensity(Vector3 intensity);
	Vector3 GetIlluminIntensity();

};

#endif
