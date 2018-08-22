#ifndef MATERIAL_H
#define MATERIAL_H
#include <Texture.h>
#include <Vector3.h>
#include <EagleLog.h>
#include <map>
#include <string>
#include <vector>
#include <Transform.h>
class RenderOfCamera;
class Shader;
using namespace std;
class Material{
private:
	map<string,Texture> textureMap;
	map<string,Texture>::iterator textureMapIte;

	map<string,Vector3> vector3Map;
	map<string,float> floatMap;

	vector<Shader*> shaderList;
//	Texture texture;
//	Vector3 color;
//	float specularIntensity;
//	float specularPower;
public:
	Material();

	void AddShader(Shader* shader);

	void AddTexture(string name,Texture texture);

	Texture GetTexture(string name);

	void AddVector3(string name,Vector3 target);

	Vector3 GetVector3(string name);

	void AddFloat(string name,float target);

	float GetFloat(string name);
    void Render(Transform *trans, RenderOfCamera* renderOfCam);
	void Finalize();
	void Pause();
	void Resume();
	void ApplicationQuit();
};

#endif
