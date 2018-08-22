#include "MeshResource.h"

MeshResource::MeshResource(int numVerticeSize,int indicsSize,size_t textureDataOffset):
numVerticeSize(numVerticeSize),indicsSize(indicsSize),textureDataOffset(textureDataOffset*numVerticeSize)
,refCount(1)
{

	glGenBuffers(1,&vbo);
    glGenBuffers(1,&ibo);

}



void MeshResource::Finalize(){

	glDeleteBuffers(1,&vbo);
	glDeleteBuffers(1,&ibo);
}


GLuint MeshResource::GetVbo(){

	return vbo;
}


GLuint MeshResource::GetIbo(){

	return ibo;
}

void MeshResource::SetNumVerticeSize(int numVerSize){

	this->numVerticeSize=numVerSize;
}

void MeshResource::SetIndicsSize(int indicsSize){

	this->indicsSize=indicsSize;
}

void MeshResource::SetTextureDataOffset(size_t textureDataOff){


	this->textureDataOffset=textureDataOff;
}

int MeshResource::GetNumVerticeSize(){

	return this->numVerticeSize;
}

int MeshResource::GetIndicsSize(){

	return this->indicsSize;
}

size_t MeshResource::GetTextureDataOffset(){

	return this->textureDataOffset;

}

void MeshResource::AddReference(){

	refCount++;
}

bool MeshResource::RemoveReference(){

	refCount--;
	return refCount==0;
}

