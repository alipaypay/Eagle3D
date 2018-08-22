#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H
#include <GLES2/gl2.h>
class TextureResource{
private:
	GLuint textureId;
	int refCount;
public:
	TextureResource(int textureId);
	virtual void Finalize();

	int GetTextureId();

	void AddReference();
	bool RemoveReference();


};

#endif
