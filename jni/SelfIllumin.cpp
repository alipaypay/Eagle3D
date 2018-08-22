#include <SelfIllumin.h>

 SelfIllumin* SelfIllumin::Instance;

 SelfIllumin* SelfIllumin::GetInstance(){

	 SelfIllumin::Instance=new SelfIllumin();
	 return SelfIllumin::Instance;
 }


 SelfIllumin::SelfIllumin():Shader(){

	AddVertexShaderFromFile("Self-Illumin.vs");
	AddFragmentShaderFromFile("Self-Illumin.fs");
	SetAttribLocation("position",0);
	SetAttribLocation("texCoord",1);

	CompileShader();
	AddUniform("MVP");
	AddUniform("selfIlluminIntensity");
}
void SelfIllumin::UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam){

	Matrix4x4 worldMatrix=trans->GetTransformation();

	Matrix4x4 projectedMatrix=renderCam->GetMainCamera()->GetViewProjection()*worldMatrix;

	material.GetTexture("diffuse").Bind();

	SetUniformM("MVP",projectedMatrix);
	SetUniform3f("selfIlluminIntensity",GetIlluminIntensity());

}

void SelfIllumin::SetSelfIlluminIntensity(Vector3 intensity){

	illuminIntensity=intensity;
}

Vector3 SelfIllumin::GetIlluminIntensity(){
	return illuminIntensity;

}
