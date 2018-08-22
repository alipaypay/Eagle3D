#ifndef QUATERNION_H
#define QUATERNION_H
#include <math.h>
#include "Matrix4x4.h"
#include "Vector3.h"
#include "EagleMath.h"
class Quaternion{
public:
	float x,y,z,w;

	Quaternion(float x,float y,float z,float w);

	Quaternion(Vector3 axis,float angle);

	Quaternion();

	bool operator !=(const Quaternion &q) const;

	float Length();

	Quaternion& Normalize();

	Quaternion& Conjugate();

	Quaternion& Mul(Quaternion r);

	Quaternion& Mul(float x,float y,float z);

	Matrix4x4 ToRotationMatrix();

	Vector3 GetForward();

	Vector3 GetBack();

	Vector3 GetUp();

	Vector3 GetDown();

	Vector3 GetLeft();

	Vector3 GetRight();

	void Set(Quaternion copy);
	//Quaternion& InitRotation(Vector3 axis,float angle);

	 Quaternion Mul(float r);

};
#endif


