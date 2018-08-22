#ifndef MESH_RESOURCE_H
#define MESH_RESOURCE_H
#include <GLES2/gl2.h>
class MeshResource{
private:
	GLuint vbo;
	GLuint ibo;
	int numVerticeSize;
	int indicsSize;
	size_t textureDataOffset;
	int refCount;
public:
	MeshResource(int numVerticeSize,int indicsSize,size_t textureDataOffset);
	virtual void Finalize();
	GLuint GetVbo();
	GLuint GetIbo();
	void SetNumVerticeSize(int numVerSize);
	void SetIndicsSize(int indicsSize);
	void SetTextureDataOffset(size_t textureDataOff);
	int GetNumVerticeSize();
	int GetIndicsSize();
	size_t GetTextureDataOffset();
	void AddReference();
	bool RemoveReference();
};

#endif
