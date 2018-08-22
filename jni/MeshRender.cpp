#include "MeshRender.h"

MeshRender::MeshRender(Mesh mesh,Material mat):mesh(mesh),material(mat){

	currShader=NULL;

}


void MeshRender::Render(Shader* shader,RenderOfCamera* renderOfCam){

	if(currShader==NULL){
		currShader=shader;
	}
	shader->Bind();
	shader->UpdateUniforms(this->GetTransform(),material,renderOfCam);
	material.Render(this->GetTransform(),renderOfCam);
	mesh.Draw();


}


void MeshRender::Update(float delta){


//	trans->SetTranslation(0.0f,-1.0f,5.0f);
}


Shader* MeshRender::GetCurrentShader(){


	return currShader;
}

void MeshRender::Pause(){

	mesh.Finalize();
	material.Pause();
	material.Finalize();
	currShader=NULL;
	delete currShader;

}

void MeshRender::Resume(){

	material.Resume();
}

void MeshRender::ApplicationQuit(){
	mesh.Finalize();
	material.Finalize();
	currShader=NULL;
	delete currShader;
}
