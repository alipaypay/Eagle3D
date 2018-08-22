#ifndef INDEXED_MODEL_H
#define INDEXED_MODEL_H
#include <vector>
#include "Vector3.h"
#include "Tools.h"
using namespace std;
class IndexedModel{
private:
	vector<Vector3> positions;
	vector<Vector2> textureCoords;
	vector<Vector3> normals;
	vector<int> indices;
public:
	IndexedModel();

	void CalcNormals();

	vector<Vector3>& GetPositions();
	vector<Vector2>& GetTextureCoords();
	vector<Vector3>& GetNormals();
	vector<int>& GetIndices();

};
#endif
