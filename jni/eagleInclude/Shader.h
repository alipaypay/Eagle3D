#ifndef SHADER_H
#define SHADER_H
#include <GLES2/gl2.h>
#include "EagleLog.h"
#include <stdlib.h>
#include <map>
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Material.h"
#include <string>
#include <android/asset_manager.h>
#include "CoreActivity.h"
#include "Transform.h"
class RenderOfCamera;
using namespace std;
class Shader{
private:
	//RenderOfCamera* renderCam;

	GLuint program;
	map<const char*,int> uniforms;
	int FindUniformLocation(const char* uniformName);
	static char* ReadResource(const char* fileName);

	//Load shader in external card
	static char* LoadShader(const char* fileName);

	//load shader in assets folder
	static char* ReadAssetsShader(const char* fileName);
public:
	Shader();

	virtual void AddVertexShaderFromFile(const char* vertFileName);

	virtual void AddFragmentShaderFromFile(const char* fragFileName);

	virtual void AddVertexShader(const char* vert);

	virtual void AddFragmentShader(const char* frag);

	virtual void AddProgram(const char* shader,int type);

	virtual void AddUniform(const char* uniform);

	virtual void SetUniformi(const char* uniformName,int val);

	virtual void SetUniformf(const char* uniformName,float val);

	virtual void SetUniform3f(const char* uniformName,Vector3 val);

	virtual void SetUniformM(const char* uniformName,Matrix4x4 val);

//	virtual void SetUniform(string uniformName,BaseLight  baseLight);
//
//	virtual void SetUniform(string uniformName,DirectionalLight  directionalLight);
//
//	virtual void SetUniform(std::string uniformName,PointLight* pointLight);

	virtual void SetAttribLocation(const char* attributeName,int location);

	virtual void UpdateUniforms(Transform* trans,Material material,RenderOfCamera* renderCam);

	virtual void CompileShader();

	virtual void Bind();

	virtual void UnBind();

//	void SetRenderOfCamera(RenderOfCamera* renderCam);
//
//	RenderOfCamera* GetRenderOfCamera();

};

#endif
