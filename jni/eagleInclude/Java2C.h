#ifdef _Android_
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <vector>
#include "EagleLog.h"
#include <string>
using namespace std;
/* Header for class www_eagle3d_com_Java2C */

#ifndef _Included_www_eagle3d_com_Java2C
#define _Included_www_eagle3d_com_Java2C
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     www_eagle3d_com_Java2C
 * Method:    SetPackageCodePath
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_www_eagle3d_com_Java2C_SetPackageCodePath
  (JNIEnv *, jclass, jstring);

/*
 * Class:     www_eagle3d_com_Java2C
 * Method:    SetEaglePackageClassNames
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_www_eagle3d_com_Java2C_SetEaglePackageClassNames
  (JNIEnv *, jclass, jobjectArray);



/*
 * Class:     www_eagle3d_com_Java2C
 * Method:    SetEagleClass
 * Signature: (Ljava/lang/Class;)V
 */
JNIEXPORT void JNICALL Java_www_eagle3d_com_Java2C_SetEagleClass
  (JNIEnv *, jclass, jclass);

#ifdef __cplusplus
}

class Java2C{
public:
	static string PACKAGE_CODE_PATH;

	static vector<string> CLASS_NAMES;

	static jclass CURRENT_CLASS;

	static JNIEnv *JNI_ENV;

	static jclass EAGLE_ACTIVITY_CLASS;
};


#endif
#endif
#endif
