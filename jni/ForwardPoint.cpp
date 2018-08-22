#include "ForwardPoint.h"
#include "RenderOfCamera.h"
 ForwardPoint* ForwardPoint::Instance;

 ForwardPoint* ForwardPoint::GetInstance(){

	 ForwardPoint::Instance=new ForwardPoint();
	 return ForwardPoint::Instance;
 }


 ForwardPoint::ForwardPoint():Shader(){

	AddVertexShaderFromFile("forward-point.vs");
	AddFragmentShaderFromFile("forward-point.fs");
	SetAttribLocation("position",0);
	SetAttribLocation("texCoord",1);
	SetAttribLocation("normal",2);
	CompileShader();
	AddUniform("model");
	AddUniform("MVP");
	AddUniform("eyePos");
	AddUniform("specularIntensity");

	AddUniform("pointLight.base.color");
	AddUniform("pointLight.base.intensity");
	AddUniform("pointLight.atten.constant");
	AddUniform("pointLight.atten.linear");
	AddUniform("pointLight.atten.exponent");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");


}
void ForwardPoint::UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam){
	Matrix4x4 worldMatrix=trans->GetTransformation();
	Matrix4x4 projectedMatrix=renderCam->GetMainCamera()->GetViewProjection()*worldMatrix;

	material.GetTexture("diffuse").Bind();
	SetUniformM("model",worldMatrix);
	SetUniformM("MVP",projectedMatrix);
	SetUniform3f("eyePos",renderCam->GetMainCamera()->GetTransform()->GetTransformPos());
	SetUniformf("specularIntensity",material.GetFloat("specularIntensity"));

	SetUniform3f("pointLight.base.color",renderCam->GetActiveLight()->Color);
	SetUniformf("pointLight.base.intensity",renderCam->GetActiveLight()->Intensity);
	SetUniformf("pointLight.atten.constant",((PointLight*)(renderCam->GetActiveLight()))->GetConstant());
	SetUniformf("pointLight.atten.linear",((PointLight*)(renderCam->GetActiveLight()))->GetLinear());
	SetUniformf("pointLight.atten.exponent",((PointLight*)(renderCam->GetActiveLight()))->GetExponent());
	SetUniform3f("pointLight.position",((PointLight*)(renderCam->GetActiveLight()))->GetTransform()->GetTransformPos());
	SetUniformf("pointLight.range",((PointLight*)(renderCam->GetActiveLight()))->GetRange());





}
