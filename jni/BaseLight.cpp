#include "BaseLight.h"
#include "RenderOfCamera.h"
BaseLight::BaseLight(Vector3 color,float intensity):Color(color),Intensity(intensity){
	shader=NULL;
}

BaseLight::BaseLight():Color(Vector3(0.0f,0.0f,0.0f)),Intensity(0.0f){
	shader=NULL;

}
BaseLight& BaseLight::operator = (const BaseLight &rBaseLight){

	this->Color=rBaseLight.Color;
	this->Intensity=rBaseLight.Intensity;
	return *this;
}

void BaseLight::SetShader(Shader* shader){

	this->shader=shader;
}

void BaseLight::AddToRenderOfCamera(RenderOfCamera* renderOfCam){


	renderOfCam->AddLight(this);
}

Shader* BaseLight::GetShader(){

	return shader;

}

void BaseLight::Pause(){

	shader=NULL;
	delete shader;
}

void BaseLight::Resume(){


}

void BaseLight::ApplicationQuit(){
	shader=NULL;
	delete shader;



}
