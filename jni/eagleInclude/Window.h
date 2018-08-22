#ifndef WINDOW_H
#define WINDOW_H

#include <EGL/egl.h>
#include "Game.h"
#include "RenderingEngine.h"
 class Window{
public:
	static void Update(float delta);
	static void Render();

	static void WindowStart();
	static void WindowAwake();
	static void OnFocus();
	static void OnLoseFocus();

	static void Resize(int32_t width,int32_t height);
	static void Pause();
	static void Stop();
	static void OnSurfaceDestroy();
	static void OnApplicationQuit();
	static void Resume();
	static void LowMemory();
	static void InitWindowSize(int32_t width,int32_t height);
	static int32_t GetWindowWidth();
	static int32_t GetWindowHeight();
	static Vector2 GetWindowCenter();
	static RenderingEngine* GetRenderingEngine();

private:
	static RenderingEngine* renderingEngine;
	static int32_t WIDTH;
	static int32_t HEIGHT;
};
#endif
