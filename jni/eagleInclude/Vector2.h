
#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include "EagleMath.h"
#define max(a, b)  (((a) >= (b)) ? (a) : (b))
class Vector2{
public:
	float x,y;
	Vector2();
	Vector2(const Vector2 &copy);
	Vector2(float vx,float vy);
	Vector2 &operator=(const Vector2 &v);
	bool operator ==(const Vector2 &v) const;
	Vector2 Rotate(float angle);

	bool operator !=(const Vector2 &v) const;
	void Zero();
	Vector2 operator -() const;
	Vector2 operator +(const Vector2 &v)const;
	Vector2 operator -(const Vector2 &v)const;
	Vector2 operator *(float value)const;
	Vector2 operator /(float value)const;
	Vector2 &operator +=(const Vector2 &v);
	Vector2 &operator -=(const Vector2 &v);
	Vector2 &operator *=(float value);
	Vector2 &operator /=(float value);
	void Normalize();

	float Dot(const Vector2 &v) const;
	float Length(const Vector2 &v);
	static float Distance(const Vector2 &v1,const Vector2 &v2);

	Vector2 Lerp(Vector2 dest,float lerpFactor);
	//Cross product
	Vector2  CrossProduct(const Vector2 &v)const;
	float Max();

};
#endif
