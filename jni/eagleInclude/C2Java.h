#ifdef _Android_
#ifndef C_TO_JAVA
#define C_TO_JAVA
#include "EagleLog.h"
#include <jni.h>
#include "Java2C.h"
#include "Tools.h"
#include <map>
#include <android_native_app_glue.h>

using namespace std;
class C2Java{
public:
	 C2Java(const char* className,ANativeActivity* activity,bool isGetEagleDevelopSubClass);

	 C2Java(jclass currentClass,ANativeActivity* activity,bool isGetEagleDevelopSubClass);



	 ~C2Java();
	 jclass GetCurrentJavaClass();

	 JNIEnv* GetCurrentJNIEnv();
	 //get current class
	 jclass GetObjectClass(const char* className,ANativeActivity* currentActivity);
	 //new class and no arguments in constructor
	 jobject NewNonArgsConstructor(jclass classTarget);

	// jclass GetCurrentClassOfSuperClass(jclass subClass,const char* className);

	 bool IsAssignableFromParentClass(jclass superClass,jclass subClass);

	 void CallJavaVoidMethod(const char* funcName,const char* classType);

	 void AddEagleSubClassesObj(jclass subClz,jobject subObj);

	 map<jclass,jobject> GetEagleSubClassesObj();
private:

	 void Init(ANativeActivity* activity);

	 //vector<jobject> eagleSubClassesObj;

	 map<jclass,jobject> eagleSubClassesObj;

	 ANativeActivity* currentActivity;
	 JNIEnv *jni_env;
	 jclass cls_Env;
	 jobject obj;



};

#endif
#endif
