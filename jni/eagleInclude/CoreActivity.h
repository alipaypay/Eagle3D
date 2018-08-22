#ifndef CORE_ACTIVITY_H
#define CORE_ACTIVITY_H
#include <android_native_app_glue.h>
class CoreActivity{
private:
	static ANativeActivity* activity;
public:
	static void SetActivity(ANativeActivity* activity);
	static ANativeActivity* GetActivity();
};

#endif
