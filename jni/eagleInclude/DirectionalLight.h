#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT
#include "BaseLight.h"
#include "ForwardDirectional.h"
class DirectionalLight : public BaseLight{
private:
	Vector3 lightDirection;
public:
	Vector3 GetLightDirection();

	DirectionalLight(Vector3 color,float intensity);

//	DirectionalLight& operator =(const DirectionalLight& rDirLight);
};

#endif
