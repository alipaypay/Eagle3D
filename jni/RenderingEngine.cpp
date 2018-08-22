#include "RenderingEngine.h"

 int32_t RenderingEngine::width;
 int32_t RenderingEngine::height;


RenderingEngine::RenderingEngine(){
	RenderingEngine::SetClearColor(0.192f,0.302f,0.475f);
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	if(renderCam!=NULL){
		renderCam=NULL;
	}
	renderCam=new RenderOfCamera();
	if(forwardAmbient!=NULL){

		forwardAmbient=NULL;
	}
	forwardAmbient=ForwardAmbient::GetInstance();

	//forwardAmbient->SetRenderOfCamera(renderCam);

}

void RenderingEngine::Render(GameObject* obj){
	ClearScreen();
	renderCam->ClearLights();
	renderCam->AddToRenderOfCamera(obj,renderCam);
	obj->Render(forwardAmbient,renderCam);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL);

	renderCam->Render(obj);
	//obj->Render(forwardDirectional);
	glDepthFunc(GL_LESS);
	glDepthMask(true);
	glDisable(GL_BLEND);

}

void RenderingEngine::Pause(GameObject* obj){

	obj->Pause();
}

void RenderingEngine::Resume(GameObject* obj){
	obj->Resume();

}

void RenderingEngine::ApplicationQuit(GameObject* obj){

	obj->ApplicationQuit();
}


void RenderingEngine::ClearScreen(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void RenderingEngine::SetTextures(bool enable){
	if(enable){
		glEnable(GL_TEXTURE_2D);
	}else{

		glDisable(GL_TEXTURE_2D);
	}



}

void RenderingEngine::UnBindTexture(){
	glBindTexture(GL_TEXTURE_2D,0);


}

void RenderingEngine::SetClearColor(float colorX,float colorY,float colorZ){
	//0.192f 0.302f 0.475f
	glClearColor(colorX,colorY,colorZ,1.0f);

}

void RenderingEngine::SetWindowSize(int32_t width,int32_t height){
	RenderingEngine::width=width;
	RenderingEngine::height=height;
	RenderOfCamera::SetWindowSize(width,height);

}
int32_t RenderingEngine::GetWindowWidth(){
	return RenderingEngine::width;
}

int32_t RenderingEngine::GetWindowHeight(){
	return RenderingEngine::height;
}



