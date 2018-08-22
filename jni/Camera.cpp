#include "Camera.h"
#include "RenderOfCamera.h"
#include <Window.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <math.h>
 const Vector3 Camera::yAxis(0.0f,1.0f,0.0f);

int Camera::camId=0;
 Camera::Camera():fov(70.0f),aspect(1.0f),zNear(0.01f),zFar(1000.0f),viewPortRect(0,0,Window::GetWindowWidth(),Window::GetWindowHeight()){

	 	projection.InitPerspective(70.0f,1.0f,0.01f,1000.0f);


 }

Camera::Camera(float fov,float aspect,float zNear,float zFar):fov(fov),aspect(aspect),zNear(zNear),zFar(zFar),
		viewPortRect(0,0,Window::GetWindowWidth(),Window::GetWindowHeight()){

	projection.InitPerspective(fov,aspect,zNear,zFar);
}

void Camera::SetTargetTexture(Texture* texture){



}


void Camera::GenerateTexture(){
	GLuint *frameID=(GLuint*)&camId;
	GLuint renderId;
	glGenFramebuffers(1,frameID);
	glBindFramebuffer(GL_FRAMEBUFFER,*frameID);

	glGenRenderbuffers(1,&renderId);
	glBindRenderbuffer(GL_RENDERBUFFER,renderId);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,viewPortRect.width,viewPortRect.height);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,renderId);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Camera::SetCameraRect(float x,float y,float width,float height){
	viewPortRect.SetRect(x,y,width,height);
}

void Camera::Move(Vector3 dir,float amt){

	GetTransform()->SetPosition(GetTransform()->GetPosition()+=dir*amt);

}


Matrix4x4 Camera::GetViewProjection(){
	Matrix4x4 cameraRotationMatrix;
	cameraRotationMatrix=GetTransform()->GetTransformRotation().Conjugate().ToRotationMatrix();

	Vector3 cameraPos=this->GetTransform()->GetTransformPos()*(-1);
	//Camera translation matrix
	Matrix4x4 camTranslationMatrix;
	camTranslationMatrix.InitTranslation(cameraPos.x,cameraPos.y,cameraPos.z);
	return projection*(cameraRotationMatrix*(camTranslationMatrix));

}

void Camera::AddToRenderOfCamera(RenderOfCamera* renderOfCam){

	renderOfCam->AddCamera(this);
}


void Camera::Render(Shader* shader,RenderOfCamera* renderOfCam){


}

static void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
    GLfloat top = zNear * ((GLfloat) tan(fovy * M_PI / 360.0));
    GLfloat bottom = -top;
    GLfloat left = bottom * aspect;
    GLfloat right = top * aspect;
    glFrustumf(left, right, bottom, top, zNear, zFar);
}

void Camera::Render(){



}

void Camera::Update(float delta){


}


