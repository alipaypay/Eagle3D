#include "SpotLight.h"


SpotLight::SpotLight(Vector3 color,float intensity,Vector3 atten,float cutOff):PointLight( color, intensity, atten),
				     cutOff(cutOff)
{

	SetShader(ForwardSpot::GetInstance());
}

Vector3 SpotLight::GetDirection(){

	return this->GetTransform()->GetTransformRotation().GetForward();
}
