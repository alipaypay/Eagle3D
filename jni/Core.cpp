#include "Core.h"

 ANativeActivity* Core::activity;
 Core::Core():lastTime(0.0),isRunning(false),unProcessTime(0),frameTime(1.0/FRAME_CAP),render(false),
 frames(0),frameCounter(0)
 {
	 isRunning=false;
	 Window::WindowAwake();
 }


JNIEnv* Core::GetJNIEnv(){

	return GetActivity()->env;
}


const char* Core::GetInternalDataPath(){

	return activity->externalDataPath;
}
const char* Core::GetExternalDataPath(){

	return activity->internalDataPath;
}


ANativeActivity* Core::GetActivity(){
	return Core::activity;
}
void Core::SetActivity(ANativeActivity* activity){
	Core::activity=activity;
	CoreActivity::SetActivity(activity);

}
void Core::LowMemory(){

	Window::LowMemory();
}
void Core::GetFocus(){
	Window::OnFocus();
}
void Core::LoseFocus(){
	Window::OnLoseFocus();

}

void Core::Render(){

	if(isRunning){
		render=false;
		double startTime=TimeControl::GetTime();
		double passTime=startTime-lastTime;
		lastTime=startTime;
		unProcessTime+=passTime;
		frameCounter+=passTime;
		while(unProcessTime>frameTime){

			render=true;
			unProcessTime-=frameTime;
			Window::Update((float)frameTime);
			if(frameCounter>=1.0){

				LOGI("Core Frame:%i",frames);
				frames=0;
				frameCounter=0;
			}
		}
		if(render){

			Window::Render();
			frames++;
		}else{
			//sleep(Mill)
			sleep(0.001);
		}

	}

}
void Core::Start(){
	if(isRunning){
		return;
	}

	//RenderUtil::InitGraphics();
	isRunning=true;
	Window::WindowStart();
	lastTime=TimeControl::GetTime();

}
void Core::Resize(int32_t width,int32_t height){
	Window::Resize(width,height);
}
void Core::Resume(){
	if(isRunning){
			return;
		}
	//RenderUtil::InitGraphics();
	isRunning=true;
	Window::Resume();
	lastTime=TimeControl::GetTime();

}
void Core::Stop(){
	Window::Stop();
	if(!isRunning){
			return;
		}
	isRunning=false;

}

void Core::Pause(){
	Window::Pause();
	if(!isRunning){
		return;
	}
	isRunning=false;

}
void Core::OnSurfaceDestroy(){

	Window::OnSurfaceDestroy();
}
void Core::OnApplicationQuit(){

	Window::OnApplicationQuit();

}

