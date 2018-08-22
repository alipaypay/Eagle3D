#include "ForwardAmbient.h"
#include "RenderOfCamera.h"
 ForwardAmbient* ForwardAmbient::Instance;

 ForwardAmbient* ForwardAmbient::GetInstance(){

	 ForwardAmbient::Instance=new ForwardAmbient();
	 return ForwardAmbient::Instance;
 }


 ForwardAmbient::ForwardAmbient():Shader(){

	AddVertexShaderFromFile("forward-ambient.vs");
	AddFragmentShaderFromFile("forward-ambient.fs");
	SetAttribLocation("position",0);
	SetAttribLocation("texCoord",1);

	CompileShader();
	AddUniform("MVP");
	AddUniform("ambientIntensity");
}
void ForwardAmbient::UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam){

	Matrix4x4 worldMatrix=trans->GetTransformation();

	Matrix4x4 projectedMatrix=renderCam->GetMainCamera()->GetViewProjection()*worldMatrix;

	material.GetTexture("diffuse").Bind();

	SetUniformM("MVP",projectedMatrix);
	SetUniform3f("ambientIntensity",renderCam->GetAmbientLight());

}
