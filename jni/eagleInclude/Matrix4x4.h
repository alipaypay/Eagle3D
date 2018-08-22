#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <math.h>
#include "EagleMath.h"
#include "EagleLog.h"
#include "Vector3.h"
class Matrix4x4{
public:
	float mat[4][4];

	Matrix4x4(float valMat[4][4]);

	Matrix4x4();

	Vector3 Transform(Vector3 r);
	//opengl
	//	|m00 m10 m20 m30|
	//  |m01 m11 m21 m31|
	//  |m02 m12 m22 m32|
	//  |m03 m13 m23 m33|
	Matrix4x4& InitRotation(float x,float y,float z);

	void InitScale(float x,float y,float z);

	void InitPerspective(float fov,float aspectRatio,float zNear,float zFar);

	void InitTranslation(float x,float y,float z);

	void InitRotation(Vector3 forward,Vector3 up);

	void InitRotation(Vector3 forward,Vector3 up,Vector3 right);

	float* GetMatLinearArray();


	void SetMatrix(float copMat[4][4]);

	Matrix4x4 operator*(Matrix4x4 tarM);


	float GetValue(int x,int y);

	void SetValue(int x,int y,float value);

	Matrix4x4& Identity();

	Matrix4x4& InitOrthoGraphic(float left,float right,float top,float bottom,float near,float far);

	void Print();
};
#endif
