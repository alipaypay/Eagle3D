#include "Transform.h"

Transform::Transform(){
	SetPosition(0.0f,0.0f,0.0f);
	SetRotation(0.0f,0.0f,0.0f,1.0f);
	SetScale(1.0f,1.0f,1.0f);
	this->oldPosition=NULL;
	this->parent=NULL;
	parentMatrix=Matrix4x4().Identity();
}

Vector3 Transform::GetPosition(){

	return this->position;

}

void Transform::SetPosition(Vector3 position){

	SetPosition(position.x,position.y,position.z);

}

Matrix4x4 Transform::GetParentMatrix(){
	if(parent != NULL && parent->HasChange()){

			parentMatrix=parent->GetTransformation();

	}
	return parentMatrix;
}


void Transform::SetPosition(float x,float y,float z){

	this->position.x=x;
	this->position.y=y;
	this->position.z=z;

}

Matrix4x4 Transform::GetTransformation(){

	Matrix4x4 translationMat;
	translationMat.InitTranslation(GetPosition().x,GetPosition().y,GetPosition().z);

	Matrix4x4 rotationMat;
	rotationMat=rotation.ToRotationMatrix();

	Matrix4x4 scaleMat;
	scaleMat.InitScale(GetScale().x,GetScale().y,GetScale().z);

	return GetParentMatrix()*translationMat*rotationMat*scaleMat;
}


Quaternion Transform::GetRotation(){
	return rotation;
}

void Transform::SetRotation(Quaternion rotation){

	SetRotation(rotation.x,rotation.y,rotation.z,rotation.w);
}

void Transform::SetRotation(float x,float y,float z,float w){
		this->rotation.x=x;
		this->rotation.y=y;
		this->rotation.z=z;
		this->rotation.w=w;
}

Vector3 Transform::GetScale(){

	return scale;
}

void Transform::SetScale(Vector3 scale){

	SetScale(scale.x,scale.y,scale.z);
}

void Transform::SetScale(float x,float y,float z){

	this->scale.x=x;
	this->scale.y=y;
	this->scale.z=z;
}

void Transform::SetParent(Transform* trans){

	this->parent=trans;
}

Transform* Transform::GetParent(){

	return this->parent;
}

bool Transform::HasChange(){

	if(this->parent!=NULL && this->parent->HasChange()){
			return true;
	}
	Vector3 temp(this->oldPosition->x,this->oldPosition->y,this->oldPosition->z);
	if(this->position!=temp){
		return true;
	}

	if(this->scale!=this->oldScale){
		return true;
	}

	if(this->rotation != this->oldRotation){
	   return true;
	}
	return false;
}

Vector3 Transform::GetTransformPos(){
	return GetParentMatrix().Transform(this->position);
}

Quaternion Transform::GetTransformRotation(){

	Quaternion parentRotation(0.0f,0.0f,0.0f,1.0f);
	if(parent!=NULL){

		parentRotation=parent->GetTransformRotation();
	}
	return parentRotation.Mul(this->rotation);
}


void Transform::Update(){

	if(this->oldPosition!=NULL){

		this->oldPosition->Set(this->position);

		this->oldRotation.Set(this->rotation);

		this->oldScale.Set(this->scale);

	}else{

		this->oldPosition=new Vector3(0.0f,0.0f,0.0f);
		this->oldPosition->Set(this->position);
		this->oldPosition->Add(1.0f);

		this->oldRotation=Quaternion(0.0f,0.0f,0.0f,0.0f);
		this->oldRotation.Set(this->rotation);
		this->oldRotation.Mul(0.5f);

		this->oldScale=Vector3(0.0f,0.0f,0.0f);
		this->oldScale.Set(this->scale);
		this->oldScale.Add(1.0f);
	}

}

void Transform::Rotate(Vector3 axis,float angle){

	this->rotation=Quaternion(axis,angle).Mul(this->rotation).Normalize();

}


