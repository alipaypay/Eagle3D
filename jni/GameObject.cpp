#include "GameObject.h"

GameObject::GameObject(){

	transform=new Transform();


}


GameObject::~GameObject(){
	delete transform;
	transform=NULL;


}

void GameObject::Update(float delta){

	this->transform->Update();
	for(int i=0;i<components.size();i++){

		components[i]->Update(delta);
	}


	for(int i=0;i<childrenList.size();i++){
		childrenList[i]->Update(delta);

	}


}
void GameObject::Render(Shader* shader,RenderOfCamera* renderOfCam){
	int size=components.size();
	for(int i=0;i<size;i++){

			components[i]->Render(shader,renderOfCam);
			components[i]->Render();
	}

	for(int i=0;i<childrenList.size();i++){

			childrenList[i]->Render(shader,renderOfCam);

	}

}

void GameObject::AddChild(GameObject* child){
	LOGI("Game Object Add Start");
	childrenList.push_back(child);
	child->GetTransform()->SetParent(transform);

}

GameObject* GameObject::AddComponent(Component* component){

	component->SetParent(this);
	components.push_back(component);
	return this;

}

Transform* GameObject::GetTransform(){

	return transform;
}

void GameObject::RemoveChildAll(){
	removeResult=childrenList.begin();
	while(removeResult!=childrenList.end()){

		removeResult=childrenList.erase(removeResult);

	}

}

void GameObject::AddToRenderOfCamera(RenderOfCamera* renderOfCam){
		for(int i=0;i<components.size();i++){

			components[i]->AddToRenderOfCamera(renderOfCam);
		}


		for(int i=0;i<childrenList.size();i++){
			childrenList[i]->AddToRenderOfCamera(renderOfCam);

		}


}

void GameObject::Pause(){
		for(int i=0;i<components.size();i++){

			components[i]->Pause();
		}


		for(int i=0;i<childrenList.size();i++){
			childrenList[i]->Pause();

		}

}
void GameObject::Resume(){
			for(int i=0;i<components.size();i++){

				components[i]->Resume();
			}


			for(int i=0;i<childrenList.size();i++){
				childrenList[i]->Resume();

			}

}

void GameObject::ApplicationQuit(){
			for(int i=0;i<components.size();i++){

				components[i]->ApplicationQuit();
			}


			for(int i=0;i<childrenList.size();i++){
				childrenList[i]->ApplicationQuit();

			}


}

