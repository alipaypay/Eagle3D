#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "PointLight.h"
#include "Vector3.h"
#include "ForwardSpot.h"
class SpotLight : public PointLight{
private:
	Vector3 direction;
public:
	SpotLight(Vector3 color,float intensity,Vector3 atten,float cutOff);

	float cutOff;

	Vector3 GetDirection();
};
#endif
