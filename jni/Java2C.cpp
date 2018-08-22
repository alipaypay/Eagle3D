#ifdef _Android_
#include "Java2C.h"
 string Java2C::PACKAGE_CODE_PATH;
 vector<string> Java2C::CLASS_NAMES;
 jclass Java2C::CURRENT_CLASS;

JNIEnv *Java2C::JNI_ENV;

jclass Java2C::EAGLE_ACTIVITY_CLASS;


JNIEXPORT void JNICALL Java_www_eagle3d_com_Java2C_SetPackageCodePath
  (JNIEnv *env, jclass clz, jstring path){

	   jboolean isCopy;
	   const char* pathResult = env->GetStringUTFChars(path, &isCopy);
	   string pathStr(pathResult);
	   Java2C::PACKAGE_CODE_PATH=pathStr;
	   env->ReleaseStringUTFChars(path,pathResult);
}


JNIEXPORT void JNICALL Java_www_eagle3d_com_Java2C_SetEaglePackageClassNames
  (JNIEnv *env, jclass clz, jobjectArray objArray){
int size=env->GetArrayLength(objArray);
jboolean isCopy;
string eagleNativeActivity="EagleNativeActivity";
for(int i=0;i<size;i++){
	jstring objArr=(jstring)env->GetObjectArrayElement(objArray,i);
	const char* objArrayStr=env->GetStringUTFChars(objArr,&isCopy);
	string arrayResultStr(objArrayStr);

	string::size_type str_idx = arrayResultStr.find(eagleNativeActivity);
	if ( str_idx != string::npos )
	{
		Java2C::JNI_ENV=env;
		Java2C::EAGLE_ACTIVITY_CLASS=clz;
	}
	Java2C::CLASS_NAMES.push_back(arrayResultStr);
	env->ReleaseStringUTFChars(objArr,objArrayStr);
}

}

JNIEXPORT void JNICALL Java_www_eagle3d_com_Java2C_SetEagleClass
  (JNIEnv *env, jclass clz, jclass currentClz){

	Java2C::CURRENT_CLASS=(jclass)env->NewGlobalRef(currentClz);
	env->DeleteLocalRef(currentClz);
}

#endif
