#include "Quaternion.h"
#include "Matrix4x4.h"
Quaternion::Quaternion(float x,float y,float z,float w):x(x),y(y),z(z),w(w){

}


Quaternion::Quaternion(){
	this->x=0.0f;
	this->y=0.0f;
	this->z=0.0f;
	this->w=1.0f;
}

Quaternion::Quaternion(Vector3 axis,float angle){
	float sinHalfAngle=(float)sin(angle/2.0f);
	float cosHalfAngle=(float)cos(angle/2.0f);
	this->x=axis.x*sinHalfAngle;
	this->y=axis.y*sinHalfAngle;
	this->z=axis.z*sinHalfAngle;
	this->w=cosHalfAngle;


}


float Quaternion::Length(){

		return (float)sqrt((x*x+y*y+z*z+w*w));
	}

Quaternion& Quaternion::Normalize(){
		float length=Length();

		x/=length;
		y/=length;
		z/=length;
		w/=length;

		return *this;
	}

Quaternion& Quaternion::Conjugate(){
		this->x*=-1;
		this->y*=-1;
		this->z*=-1;
		return *this;
	}

	Quaternion& Quaternion::Mul(Quaternion r){
		this->w=this->w*r.w-this->x*r.x-this->y*r.y-this->z*r.z;
		this->x=this->x*r.w+this->w*r.x+this->y*r.z-this->z*r.y;
		this->y=this->y*r.w+this->w*r.y+this->z*r.x-this->x*r.z;
		this->z=this->z*r.w+this->w*r.z+this->x*r.y-this->y*r.x;
		//Quaternion q(x_,y_,z_,w_);
		return *this;
	}

	Quaternion& Quaternion::Mul(float x,float y,float z){
		this->w= -this->x *x-this->y*y-this->z*z;
		this->x =this->w *x+this->y*z -this->z*y;
		this->y=this->w *y+this->z*x-this->x*z;
		this->z=this->w *z+this->x*y-this->y*x;

		//Quaternion q(x_,y_,z_,w_);
		return *this;
	}
	Matrix4x4 Quaternion::ToRotationMatrix(){
		Vector3 forward=Vector3(2.0f * (x*z-w*y),2.0f*(y*z+w*x),1.0f-2.0f*(x*x+y*y));
		Vector3 up=Vector3(2.0f*(x*y+w*z),1.0f-2.0f*(x*x+z*z),2.0f*(y*z-w*x));
		Vector3 right=Vector3(1.0f-2.0f*(y*y+z*z),2.0f*(x*y-w*z),2.0f*(x*z+w*y));
		Matrix4x4 rotMat;
		rotMat.InitRotation(forward,up,right);
		return rotMat;
	}

	Vector3 Quaternion::GetForward(){
		return Vector3(0.0f,0.0f,1.0f).Rotate(*this);
	}

	Vector3 Quaternion::GetBack(){
		return Vector3(0.0f,0.0f,-1.0f).Rotate(*this);
	}

	Vector3 Quaternion::GetUp(){
		return Vector3(0.0f,1.0f,0.0f).Rotate(*this);
	}

	Vector3 Quaternion::GetDown(){

		return Vector3(0.0f,-1.0f,0.0f).Rotate(*this);
	}

	Vector3 Quaternion::GetLeft(){
		return Vector3(-1.0f,0.0f,0.0f).Rotate(*this);
	}

	Vector3 Quaternion::GetRight(){
		return Vector3(1.0f,0.0f,0.0f).Rotate(*this);

	}

	bool Quaternion::operator !=(const Quaternion &q) const{

			return x!=q.x || y!=q.y || z!=q.z || w!=q.w;
	}


	void Quaternion::Set(Quaternion copy){

		this->x=copy.x;
		this->y=copy.y;
		this->z=copy.z;
		this->w=copy.w;
	}

	Quaternion Quaternion::Mul(float r){


		return Quaternion(x * r, y * r, z * r, w * r);
	}




