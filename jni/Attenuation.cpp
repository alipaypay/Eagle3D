#include "Attenuation.h"

Attenuation::Attenuation(float constant,float linear,float exponent):Constant(constant),
Linear(linear),Exponent(exponent)
{
}

Attenuation::Attenuation():Constant(0.0f),
		Linear(0.0f),Exponent(0.0f){

}
