#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "BaseLight.h"
//#include "Attenuation.h"
#include "ForwardPoint.h"

class PointLight :public BaseLight{
private:
	float range;
	static const int COLOR_DEPTH;
public:
	PointLight(Vector3 color,float intensity,Vector3 atten);
	PointLight();

	Vector3 Atten;
	virtual float GetConstant();
	virtual float GetLinear();
	virtual float GetExponent();

	virtual float SetConstant(float constant);
	virtual float SetLinear(float linear);
	virtual float SetExponent(float exponent);

	virtual float GetRange();
	virtual void SetRange(float range);
};
#endif
