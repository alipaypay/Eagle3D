#ifndef GAME_H
#define GAME_H

#include "MeshRender.h"
#include <EGL/egl.h>
#include "Mesh.h"
#include "Core.h"
#include <jni.h>
#include <vector>
#include "TimeControl.h"
#include "EagleLog.h"
#include <math.h>
#include "Transform.h"
#include "Camera.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "GameObject.h"
#include "Camera.h"
#include "RenderingEngine.h"
#ifdef _Android_
	#include "C2Java.h"
	#include "Java2C.h"
#endif

using namespace std;
class Game{
public:
	Game();
	void Awake();
	void Start();
	void Update(float delta);
	//void Input();
	void Render();

	void AddObject(GameObject* obj);

	void Render(RenderingEngine *renderingEngine);

	void OnFocus();
	void OnLoseFocus();
	void ApplicationQuit(RenderingEngine *renderingEngine);

	void Pause(RenderingEngine *renderingEngine);
	void Stop();
	void OnSurfaceDestroy();
	void Resume(RenderingEngine *renderingEngine);
	void LowMemory();
	void OnResize(int32_t width,int32_t height);
	void InitEagleDevelopClass();

private:
	GameObject* GetRootGameObject();

	static GameObject* root;
	GameObject* planeObj;
	MeshRender* meshRender;
	Mesh mesh;
	Material material;
	GameObject *camera;
	Camera *cam;
#ifdef _Android_
	C2Java* eagleDevelopClass;
#endif
	//Camera camera;


};
#endif
