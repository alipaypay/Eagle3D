#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

#include <GLES/gl.h>
#include "GameObject.h"
#include "ForwardAmbient.h"
#include "EagleMath.h"
#include "RenderOfCamera.h"


class RenderingEngine{
public:
	RenderingEngine();
	void Render(GameObject* obj);
	void Pause(GameObject* obj);
	void Resume(GameObject* obj);
	void ApplicationQuit(GameObject* obj);
	static void SetWindowSize(int32_t width,int32_t height);
	static int32_t GetWindowWidth();
	static int32_t GetWindowHeight();

private:
	Shader* forwardAmbient;

	RenderOfCamera* renderCam;
	static int32_t width;
	static int32_t height;
	static void ClearScreen();
	static void SetTextures(bool enable);
	static void SetClearColor(float colorX,float colorY,float colorZ);
	static void UnBindTexture();
};

#endif
