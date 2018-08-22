#include "PointLight.h"


const int PointLight::COLOR_DEPTH=256;
PointLight::PointLight(Vector3 color,float intensity,Vector3 atten):BaseLight(color,intensity),
Atten(atten)
{

	float a=atten.z;
	float b=atten.y;
	float c=atten.x-PointLight::COLOR_DEPTH * intensity * color.Max();
	SetRange((float)(-b+sqrt(b*b-4*a*c))/(2*a));
	SetShader(ForwardPoint::GetInstance());

}

PointLight::PointLight():BaseLight(),Atten(0.0f,0.0f,0.0f){

}

float PointLight::GetConstant(){
	return this->Atten.x;
}
float PointLight::GetLinear(){
	return this->Atten.y;
}
float PointLight::GetExponent(){

	return this->Atten.z;
}

float PointLight::SetConstant(float constant){

	this->Atten.x=constant;
}

float PointLight::SetLinear(float linear){
	this->Atten.y=linear;
}

float PointLight::SetExponent(float exponent){

	this->Atten.z=exponent;
}

float PointLight::GetRange(){

	return this->range;
}
void PointLight::SetRange(float range){

	this->range=range;
}
