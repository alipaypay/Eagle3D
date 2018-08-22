#include "Material.h"
#include <Shader.h>
#include <RenderOfCamera.h>
Material::Material(){

}


void Material::AddTexture(string name,Texture texture){
	textureMap[name]=texture;


}

Texture Material::GetTexture(string name){

	return textureMap[name];
}

void Material::AddVector3(string name,Vector3 target){

	vector3Map[name]=target;

}

Vector3 Material::GetVector3(string name){

	return vector3Map[name];
}

void Material::AddFloat(string name,float target){

	floatMap[name]=target;
}

float Material::GetFloat(string name){

	return floatMap[name];
}

void Material::AddShader(Shader* shader){

	shaderList.push_back(shader);
}



void Material::Render(Transform *trans,RenderOfCamera* renderOfCam){
	for(int i=0;i<shaderList.size();i++){
		  shaderList[i]->Bind();
		  shaderList[i]->UpdateUniforms(trans,*this,renderOfCam);
	}


	for(textureMapIte=textureMap.begin();textureMapIte!=textureMap.end();++textureMapIte){
		textureMapIte->second.Render();
	}
}

void Material::Finalize(){
	for(textureMapIte=textureMap.begin();textureMapIte!=textureMap.end();++textureMapIte){
			textureMapIte->second.Finalize();
	}

}
void Material::Pause(){
	for(textureMapIte=textureMap.begin();textureMapIte!=textureMap.end();++textureMapIte){
			textureMapIte->second.Pause();
		}

}

void Material::Resume(){
	for(textureMapIte=textureMap.begin();textureMapIte!=textureMap.end();++textureMapIte){
				textureMapIte->second.Resume();
			}
}

void Material::ApplicationQuit(){
	for(textureMapIte=textureMap.begin();textureMapIte!=textureMap.end();++textureMapIte){
					textureMapIte->second.ApplicationQuit();
				}

}
