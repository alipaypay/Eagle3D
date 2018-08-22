#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3 color,float intensity):BaseLight(color,intensity){


	SetShader(ForwardDirectional::GetInstance());
}



//DirectionalLight& DirectionalLight::operator =(const DirectionalLight& rDirLight){
//
//	this->lightDirection=rDirLight.lightDirection;
//	return *this;
//
//}

Vector3  DirectionalLight::GetLightDirection(){

	return this->GetTransform()->GetTransformRotation().GetForward();

}
