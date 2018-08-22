#include "ForwardDirectional.h"
#include "RenderOfCamera.h"
 ForwardDirectional* ForwardDirectional::Instance;

 ForwardDirectional* ForwardDirectional::GetInstance(){

	 ForwardDirectional::Instance=new ForwardDirectional();
	 return ForwardDirectional::Instance;
 }


 ForwardDirectional::ForwardDirectional():Shader(){

	AddVertexShaderFromFile("forward-directional.vs");
	AddFragmentShaderFromFile("forward-directional.fs");
	SetAttribLocation("position",0);
	SetAttribLocation("texCoord",1);
	SetAttribLocation("normal",2);
	CompileShader();
	AddUniform("model");
	AddUniform("MVP");
//1.forwardDirection
	AddUniform("eyePos");
	AddUniform("specularIntensity");
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");

	AddUniform("directionalLight.direction");
//2.per_vertex
//	AddUniform("lightPosition");
//	AddUniform("lightColor");
}
void ForwardDirectional::UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam){
	Matrix4x4 worldMatrix=trans->GetTransformation();
	Matrix4x4 projectedMatrix=renderCam->GetMainCamera()->GetViewProjection()*worldMatrix;

	material.GetTexture("diffuse").Bind();
	SetUniformM("model",worldMatrix);
	SetUniformM("MVP",projectedMatrix);

	//1.forwardDirection
	SetUniform3f("eyePos",renderCam->GetMainCamera()->GetTransform()->GetTransformPos());

	SetUniformf("specularIntensity",material.GetFloat("specularIntensity"));

	SetUniform3f("directionalLight.base.color",renderCam->GetActiveLight()->Color);

	SetUniform3f("directionalLight.direction",((DirectionalLight*)(renderCam->GetActiveLight()))->GetLightDirection());

	SetUniformf("directionalLight.base.intensity",renderCam->GetActiveLight()->Intensity);
	//2.per_vertex
//	SetUniform3f("lightPosition",Vector3(0.0f,0.0f,-20.0f));
//	SetUniform3f("lightColor",Vector3(1.0f,1.0f,1.0f));

}
