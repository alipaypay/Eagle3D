#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H
#include <vector>
#include "Vector3.h"
#include "OBJIndex.h"
#include "Tools.h"
#include <fstream>
#include "CoreActivity.h"
#include <android/asset_manager.h>
#include "IndexedModel.h"
#include <string>
#include <map>
using namespace std;
class OBJModel{
private:
	vector<Vector3> positions;
	vector<Vector2> textureCoords;
	vector<Vector3> normals;
	vector<OBJIndex> indices;
	bool hasTextureCoord;



	bool hasNormals;
	void OutSideModelLoad(const char* fileName);
	void InSideModelLoad(const char* fileName);
	char* ReadResource(const char* fileName);
	bool FindOBJIndex(vector <OBJIndex>::iterator beg,
		             vector <OBJIndex>::iterator end,OBJIndex val);
public:
	//Is Out Side Model
	OBJModel(const char* fileName,bool isOutSideModel);

	IndexedModel ToIndexedModel();


	OBJIndex ParseOBJIndex(string token);


};

#endif
