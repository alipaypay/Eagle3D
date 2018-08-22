#ifndef MESH_H
#define MESH_H
#include <GLES2/gl2.h>
#include <malloc.h>
#include "EagleLog.h"
#include <vector>
#include <android/asset_manager.h>
#include <fstream>
#include "CoreActivity.h"
#include "Tools.h"
#include "OBJModel.h"
#include "MeshResource.h"
#include <map>
#include <string>
using namespace std;
class Mesh{
private:
	map<string,MeshResource*> loadModels;
	map<string,MeshResource*>::iterator loadModels_iter;
	MeshResource* resource;
	string fileNameStr;
	vector<Vertex> CalcNormals(vector<Vertex> vertices,vector<int> indics);


	void AddVertices(vector<Vertex> vertices,vector<int> indics);

	void AddVertices(vector<Vertex> vertices,vector<int> indics,bool calcNormal);

	static char* ReadResource(const char* fileName);

	//Load mesh in external card
	 Mesh  LoadMesh(const char* fileName);

	//Load mesh in assets folder
	 Mesh  LoadMeshInAssets(const char* fileName);


public:
	Mesh(vector<Vertex> vertices,vector<int> indics);

	Mesh(vector<Vertex> vertices,vector<int> indics,bool calcNormal);

	Mesh(const char* fileName);

	Mesh();

	~Mesh();

	 void Finalize();

	void Draw();

};
#endif
