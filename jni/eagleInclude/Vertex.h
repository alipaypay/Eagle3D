#ifndef EAGLE_THREED_VERTEX_H
#define EAGLE_THREED_VERTEX_H
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
class Vertex{
public:
	static const int VERTEX_SIZE;
	static const int TEXTURE_COORD_SIZE;
	static const int NORMAL_COORD_SIZE;
	static const int TOTAL_SIZE;
	Vector3 Position;
	Vector2 TextureCoord;
	Vector3 Normal;
//	vector<Vector3> vertexList;
//	vector<Vector2> texCoordList;
//	vector<Vector3> normalList;
	Vertex();
	Vertex(Vector3 pos);
	Vertex(Vector3 pos,Vector2 texCoord);
	Vertex(Vector3 pos,Vector2 texCoord,Vector3 normal);
};
#endif
