#include "Vertex.h"


 const int Vertex::VERTEX_SIZE=3;
 const int Vertex::TEXTURE_COORD_SIZE=2;
 const int Vertex::NORMAL_COORD_SIZE=3;
 const int Vertex::TOTAL_SIZE=8;
Vertex::Vertex(Vector3 pos):Position(pos),TextureCoord(Vector2(0,0)),Normal(Vector3(0,0,0)){
	//vertexList.push_back(pos);

}



Vertex::Vertex(Vector3 pos,Vector2 texCoord):Position(pos),TextureCoord(texCoord),Normal(Vector3(0,0,0)){
	//vertexList.push_back(pos);
	//texCoordList.push_back(TextureCoord);

}


Vertex::Vertex(Vector3 pos,Vector2 texCoord,Vector3 normal):Position(pos),TextureCoord(texCoord),Normal(normal){



}

Vertex::Vertex():Position(Vector3(0.0f,0.0f,0.0f)),TextureCoord(Vector2(0.0f,0.0f)),Normal(Vector3(0.0f,0.0f,0.0f)){


}
