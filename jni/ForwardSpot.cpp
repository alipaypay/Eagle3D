#include "ForwardSpot.h"
#include "RenderOfCamera.h"
 ForwardSpot* ForwardSpot::Instance;

 ForwardSpot* ForwardSpot::GetInstance(){

	 ForwardSpot::Instance=new ForwardSpot();
	 return ForwardSpot::Instance;
 }


 ForwardSpot::ForwardSpot():Shader(){

	AddVertexShaderFromFile("forward-spot.vs");
	AddFragmentShaderFromFile("forward-spot.fs");
	SetAttribLocation("position",0);
	SetAttribLocation("texCoord",1);
	SetAttribLocation("normal",2);
	CompileShader();
	AddUniform("model");
	AddUniform("MVP");
	AddUniform("eyePos");
	AddUniform("specularIntensity");


	AddUniform("spotLight.pointLight.base.color");
	AddUniform("spotLight.pointLight.base.intensity");
	AddUniform("spotLight.pointLight.atten.constant");
	AddUniform("spotLight.pointLight.atten.linear");
	AddUniform("spotLight.pointLight.atten.exponent");
	AddUniform("spotLight.pointLight.position");
	AddUniform("spotLight.pointLight.range");
	AddUniform("spotLight.direction");
	AddUniform("spotLight.cutoff");


}
void ForwardSpot::UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam){
	Matrix4x4 worldMatrix=trans->GetTransformation();
	Matrix4x4 projectedMatrix=renderCam->GetMainCamera()->GetViewProjection()*worldMatrix;

	material.GetTexture("diffuse").Bind();
	SetUniformM("model",worldMatrix);
	SetUniformM("MVP",projectedMatrix);
	SetUniform3f("eyePos",renderCam->GetMainCamera()->GetTransform()->GetTransformPos());
	SetUniformf("specularIntensity",material.GetFloat("specularIntensity"));

	SetUniform3f("spotLight.pointLight.base.color",renderCam->GetActiveLight()->Color);
	SetUniformf("spotLight.pointLight.base.intensity",renderCam->GetActiveLight()->Intensity);
	SetUniformf("spotLight.pointLight.atten.constant",((PointLight*)(renderCam->GetActiveLight()))->GetConstant());
	SetUniformf("spotLight.pointLight.atten.linear",((PointLight*)(renderCam->GetActiveLight()))->GetLinear());
	SetUniformf("spotLight.pointLight.atten.exponent",((PointLight*)(renderCam->GetActiveLight()))->GetExponent());
	SetUniform3f("spotLight.pointLight.position",((PointLight*)(renderCam->GetActiveLight()))->GetTransform()->GetTransformPos());
	SetUniformf("spotLight.pointLight.range",((PointLight*)(renderCam->GetActiveLight()))->GetRange());
	SetUniform3f("spotLight.direction",((SpotLight*)(renderCam->GetActiveLight()))->GetDirection());
	SetUniformf("spotLight.cutoff",((SpotLight*)(renderCam->GetActiveLight()))->cutOff);





}
