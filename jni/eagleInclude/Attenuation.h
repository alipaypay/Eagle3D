#ifndef ATTENUATION_H
#define ATTENUATION_H
class Attenuation{
public:
	Attenuation(float constant,float linear,float exponent);
	Attenuation();
	float Constant;
	float Linear;
	float Exponent;

};
#endif
