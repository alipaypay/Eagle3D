#ifdef _Android_
#include "C2Java.h"


void C2Java::Init(ANativeActivity* activity){
		currentActivity=activity;
		int status= currentActivity->vm->GetEnv((void **) &jni_env, JNI_VERSION_1_6);
		    if(status != JNI_OK)
		    {
		        status = currentActivity->vm->AttachCurrentThread(&jni_env, NULL);
		         if(status < 0) {
		        	LOGE("Eagle3D Jni Error: Attach jni_env error");
		        }
		    }
		if(jni_env==NULL){
			LOGE("Eagle3D Jni Error:jni_env not attach current thread");
		}
}

C2Java::C2Java(const char* className,ANativeActivity* activity,bool isGetEagleDevelopSubClass){

	Init(activity);

	jclass eagleClass = GetObjectClass(className,currentActivity);
	if(eagleClass==NULL){


	}
	//LOGI("CLASS NAME CURRENT index 0:%s",Java2C::CLASS_NAMES[0]);
///////////
	cls_Env=(jclass)jni_env->NewGlobalRef(eagleClass);
	if(cls_Env==NULL){
		LOGE("Eagle3D Jni Error: Class %s not find",className);
	}

	if(!isGetEagleDevelopSubClass){
		obj=(jobject)jni_env->NewGlobalRef(NewNonArgsConstructor(cls_Env));

	}else{
		for(int i=0;i<Java2C::CLASS_NAMES.size();i++){
			jclass subClass=GetObjectClass(Java2C::CLASS_NAMES[i].c_str(),currentActivity);
			if(subClass!=NULL){
				LOGI("SUB CLASS NOT NULL~~~~~~~~");
				if(IsAssignableFromParentClass(cls_Env,subClass)){

				 jobject subObj=NewNonArgsConstructor(subClass);
				 jobject objGlobal=(jobject)jni_env->NewGlobalRef(subObj);
				 AddEagleSubClassesObj((jclass)jni_env->NewGlobalRef(subClass),objGlobal);
				 jni_env->DeleteLocalRef(subObj);
				}
			}
		}


	}
}


C2Java::C2Java(jclass currentClass,ANativeActivity* activity,bool isGetEagleDevelopSubClass){
	Init(activity);
	cls_Env=(jclass)jni_env->NewGlobalRef(currentClass);
	if(cls_Env==NULL){
			//LOGE("Eagle3D Jni Error: Class %s not find",className);
		}

		if(!isGetEagleDevelopSubClass){
			obj=(jobject)jni_env->NewGlobalRef(NewNonArgsConstructor(cls_Env));

		}else{
			for(int i=0;i<Java2C::CLASS_NAMES.size();i++){
				jclass subClass=GetObjectClass(Java2C::CLASS_NAMES[i].c_str(),currentActivity);
				if(subClass!=NULL){

					if(IsAssignableFromParentClass(cls_Env,subClass)){
					 jobject subObj=NewNonArgsConstructor(subClass);
					 jobject objGlobal=(jobject)jni_env->NewGlobalRef(subObj);
					 AddEagleSubClassesObj((jclass)jni_env->NewGlobalRef(subClass),objGlobal);
					 jni_env->DeleteLocalRef(subObj);
				}
			}
		}
	}
}


//jclass GetCurrentClassOfSuperClass(jclass subClass,const char* className){
//
//	jclass superClass=jni_env->GetSuperclass(subClass);
//
//}



jclass C2Java::GetObjectClass(const char* className,ANativeActivity* currentActivity){
		jobject nativeActivityClass=currentActivity->clazz;
		jclass acl=jni_env->GetObjectClass(nativeActivityClass);
		jmethodID getClassLoader = jni_env->GetMethodID(acl, "getClassLoader", "()Ljava/lang/ClassLoader;");
		jobject cls = jni_env->CallObjectMethod(nativeActivityClass, getClassLoader);
		jclass  classLoader = jni_env->FindClass("java/lang/ClassLoader");
		jmethodID findClass = jni_env->GetMethodID(classLoader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		jstring strClassName = jni_env->NewStringUTF(className);
		jclass eagleClass = (jclass)(jni_env->CallObjectMethod(cls, findClass, strClassName));
		jni_env->DeleteLocalRef(strClassName);
		jni_env->DeleteLocalRef(classLoader);
		return eagleClass;

}

jobject C2Java::NewNonArgsConstructor(jclass classTarget){
		jmethodID construction_id = jni_env->GetMethodID(classTarget,
					"<init>", "()V");
		jobject obj=jni_env->NewObject(classTarget,
				construction_id);
		return obj;
}


bool C2Java::IsAssignableFromParentClass(jclass superClass,jclass subClass){

	jboolean cls = jni_env->IsAssignableFrom(subClass,superClass);
	if(cls==JNI_TRUE){
		LOGI("Class Is Assignable From ParentClass");
		return true;

	}

	return false;
}

void C2Java::AddEagleSubClassesObj( jclass subClz,jobject subObj){
	LOGI("AddEagleSubClassesObj");
	eagleSubClassesObj.insert ( pair <jclass, jobject> (subClz,subObj));
}

map<jclass,jobject> C2Java::GetEagleSubClassesObj(){

	return eagleSubClassesObj;
}

C2Java::~C2Java(){
	 jni_env->DeleteGlobalRef(cls_Env);
	 jni_env->DeleteGlobalRef(obj);
	 currentActivity=NULL;
	 delete jni_env;
	 jni_env=NULL;

 }


jclass C2Java::GetCurrentJavaClass(){

	return cls_Env;

}

JNIEnv* C2Java::GetCurrentJNIEnv(){

	return jni_env;
}


void C2Java::CallJavaVoidMethod(const char* funcName,const char* argsType){

	map <jclass, jobject>::iterator sub_Iter;
	for(sub_Iter=GetEagleSubClassesObj().begin();sub_Iter!=GetEagleSubClassesObj().end();sub_Iter++){
		jmethodID mid_getExtStorage = jni_env->GetMethodID(sub_Iter->first, funcName,argsType);
		jni_env->CallVoidMethod( sub_Iter->second, mid_getExtStorage);
	}
}



#endif
