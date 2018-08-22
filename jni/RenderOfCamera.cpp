#include "BaseLight.h"
#include "RenderOfCamera.h"
#include "GameObject.h"

int32_t RenderOfCamera::width;
int32_t RenderOfCamera::height;

RenderOfCamera::RenderOfCamera(){
	ambientLight=Vector3(0.5f,0.5f,0.5f);
	activeLight=NULL;
	mainCamera=NULL;


}

void RenderOfCamera::SetMainCamera(Camera* cam){

	mainCamera=cam;
}


Camera* RenderOfCamera::GetMainCamera(){

	return mainCamera;

}

void RenderOfCamera::SetWindowSize(int32_t width,int32_t height){
	RenderOfCamera::width=width;

	RenderOfCamera::height=height;
}

int32_t RenderOfCamera::GetWindowWidth(){

	return RenderOfCamera::width;
}

int32_t RenderOfCamera::GetWindowHeight(){

	return RenderOfCamera::height;

}


Vector3 RenderOfCamera::GetAmbientLight(){

	return ambientLight;
}

void RenderOfCamera::Render(GameObject* object){

	for(int i=0;i<lights.size();i++){

		SetActiveLight(lights[i]);
		object->Render(lights[i]->GetShader(),this);

	}

}

void RenderOfCamera::AddLight(BaseLight* light){

	lights.push_back(light);

}

void RenderOfCamera::ClearLights(){
		removeLights=lights.begin();
		while(removeLights!=lights.end()){
			removeLights=lights.erase(removeLights);
		}
}

void RenderOfCamera::AddToRenderOfCamera(GameObject* object,RenderOfCamera* renderOfCam){

	object->AddToRenderOfCamera(renderOfCam);

}


BaseLight* RenderOfCamera::GetActiveLight(){


	return activeLight;
}

void  RenderOfCamera::SetActiveLight(BaseLight* light){

	activeLight=light;

}


void RenderOfCamera::AddCamera(Camera* camera){

	mainCamera=camera;

}

