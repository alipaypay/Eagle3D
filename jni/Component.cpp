#include "Component.h"
#include "GameObject.h"
Component::Component(){
	parent=NULL;


}
void Component::Render(Shader* shader,RenderOfCamera* renderOfCam){



}
void Component::Update(float delta){



}

void Component::AddToRenderOfCamera(RenderOfCamera* renderOfCam){

}

Transform* Component::GetTransform(){

	return this->parent->GetTransform();

}

void Component::SetParent(GameObject* parent){

	this->parent=parent;
}

void Component::Pause(){


}

void Component::Resume(){


}

void Component::ApplicationQuit(){


}

void Component::Render(){


}

