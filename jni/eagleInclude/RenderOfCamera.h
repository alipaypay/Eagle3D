#ifndef RENDER_OF_CAMERA
#define RENDER_OF_CAMERA
#include "Camera.h"

#include <stdint.h>
#include <vector>
using namespace std;
class BaseLight;
class GameObject;
class RenderOfCamera{
private:
	BaseLight* activeLight;
	vector<BaseLight*> lights;
	vector<BaseLight*>::iterator removeLights;
	Camera *mainCamera;
	static int32_t width;
	static int32_t height;
	Vector3 ambientLight;

public:
	RenderOfCamera();
	Vector3 GetAmbientLight();
	void SetMainCamera(Camera* cam);
	void Render(GameObject* object);
	Camera* GetMainCamera();
	static void SetWindowSize(int32_t width,int32_t height);
	static int32_t GetWindowWidth();
	static int32_t GetWindowHeight();
	void AddLight(BaseLight* light);
	void AddCamera(Camera* camera);
	void ClearLights();
	void AddToRenderOfCamera(GameObject* object,RenderOfCamera* renderOfCam);
	BaseLight* GetActiveLight();
	void SetActiveLight(BaseLight* light);
};

#endif
