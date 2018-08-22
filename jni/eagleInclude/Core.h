#ifndef CORE_H
#define CORE_H
#include <EGL/egl.h>
#include <jni.h>
#include "Window.h"
#include "TimeControl.h"
#include <unistd.h>
#include "EagleLog.h"
#include <stdlib.h>
#include <android_native_app_glue.h>
#include "CoreActivity.h"

 class Core{
public:
	Core();
	void GetFocus();
	void LoseFocus();
	void Render();
	void Start();
	void Resize(int32_t width,int32_t height);
	void Pause();
	void OnSurfaceDestroy();
	void OnApplicationQuit();
	void Stop();
	void Resume();
	void LowMemory();
	static void SetActivity(ANativeActivity* activity);
	static ANativeActivity* GetActivity();

	static const char* GetInternalDataPath();
	static const char* GetExternalDataPath();
	static JNIEnv* GetJNIEnv();
	static const double FRAME_CAP=5000.0;
private:
	bool isRunning;
	double lastTime;
	double unProcessTime;
	double frameTime;
	bool render;
	int frames;
	double frameCounter;

	static ANativeActivity* activity;
};
#endif
