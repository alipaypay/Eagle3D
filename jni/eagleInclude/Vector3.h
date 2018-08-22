

#ifndef VECTOR3_H
#define VECTOR3_H
#define max(a, b)  (((a) >= (b)) ? (a) : (b))
#include <math.h>
#include "EagleMath.h"
#include "Vector2.h"
class Quaternion;
class Vector3{
public:
	float x,y,z;
	//Constructor
	Vector3();

	//澶嶅埗鏋勯�犲嚱鏁�
	Vector3(const Vector3 &copy);
	//鐢眡锛寉锛寊涓変釜鍊煎畬鎴愬垵濮嬪寲
	Vector3(float vx,float vy,float vz);
	//璧嬪�尖�滐紳鈥濊繍绠楃
	Vector3 &operator=(const Vector3 &v);


	//姣旇緝"=="杩愮畻绗�
	bool operator ==(const Vector3 &v) const;

	bool operator !=(const Vector3 &v) const;
	//闆跺悜閲�
	void Zero();

	//涓�鍏冭繍绠楃鈥滐紞鈥�
	Vector3 operator -() const;
	//閲嶈浇鈥滐紜鈥濃�滐紞鈥濊繍绠楃
	Vector3 operator +(const Vector3 &v)const;

	Vector3 operator -(const Vector3 &v)const;
	//鏍囬噺涔橀櫎娉�
	Vector3 operator *(float value)const;
	Vector3 operator /(float value)const;

	//鑷弽杩愮畻绗�
	Vector3 &operator +=(const Vector3 &v);
	Vector3 &operator -=(const Vector3 &v);
	Vector3 &operator *=(float value);
	Vector3 &operator /=(float value);

	Vector2 GetXY();

	Vector2 GetYZ();

	Vector2 GetZX();

	Vector2 GetYX();

	Vector2 GetZY();

	Vector2 GetXZ();

	//褰掍竴鍖�
	void Normalize();

	void Set(float x,float y,float z);

	void Set(Vector3 copy);
	//鐐逛箻
	float Dot(const Vector3 &v) const;
	//Vector length
	float Length(const Vector3 &v);
	//Cross product
	Vector3 CrossProduct(const Vector3 &v)const;
	//Axis rotate
	Vector3 Rotate(Vector3 axis,float angle);
	Vector3 Rotate( Quaternion &rotation);
	//v1 vector and v2 vector distance
	static float Distance(const Vector3 &v1,const Vector3 &v2);

	Vector3 Lerp(Vector3 dest,float lerpFactor);

	Vector3 Add(float addTarget);

	float Max();

};
#endif
