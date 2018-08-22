
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <stdlib.h>
#include "Vector3.h"
#include "Matrix4x4.h"
#include "EagleLog.h"
#include "Quaternion.h"
class Transform{
private:

	Transform* parent;
//	static Camera camera;

	//the game object translation;
	Vector3 position;
	//the game object rotate the angle
	//Vector3 rotation;
	Quaternion rotation;
	//the game object scale
	Vector3 scale;

	//the game object old translation;
	Vector3 *oldPosition;
	//the game object rotate the old angle
	//Vector3 rotation;
	Quaternion oldRotation;
	//the game object old scale
	Vector3 oldScale;

	Matrix4x4 GetParentMatrix();

	Matrix4x4 parentMatrix;

public:
	Transform();

	Vector3 GetPosition();

	void SetPosition(Vector3 position);

	void SetPosition(float x,float y,float z);

	bool HasChange();

	Matrix4x4 GetTransformation();

	Vector3 GetTransformPos();

	Quaternion GetTransformRotation();

	Quaternion GetRotation();

	void SetRotation(Quaternion rotation);

	void SetRotation(float x,float y,float z,float w);

	Vector3 GetScale();

	void SetScale(Vector3 scale);

	void SetScale(float x,float y,float z);

	void SetParent(Transform* trans);

	void Rotate(Vector3 axis,float angle);

	Transform* GetParent();

	void Update();
};
#endif
