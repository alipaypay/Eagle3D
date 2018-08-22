
#ifndef EAGLE_CAMERA_H
#define EAGLE_CAMERA_H
#include <Vector3.h>
#include <Matrix4x4.h>
#include <EagleLog.h>
#include <Component.h>
#include <Texture.h>
#include <Rect.h>
class Camera : public Component{
public:
	static const  Vector3 yAxis;
	float fov;
	float aspect;
	float zNear;
	float zFar;
	Rect viewPortRect;
	float depth;
	static int camId;
	Camera();

	Camera(float fov,float aspect,float zNear,float zFar);

	void SetCameraRect(float x,float y,float width,float height);

	/***
	 * Set Texture In Target (Example:Map or other)
	 */
	void SetTargetTexture(Texture* texture);

	//Camera move
	void Move(Vector3 dir,float amt);

	Matrix4x4 GetViewProjection();

	virtual void AddToRenderOfCamera(RenderOfCamera* renderOfCam);

	virtual void Render(Shader* shader,RenderOfCamera* renderOfCam);

	virtual void Render();

	virtual void Update(float delta);

private:

	Matrix4x4 projection;
	void GenerateTexture();

};

#endif
