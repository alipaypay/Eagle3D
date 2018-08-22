#include "TextureResource.h"


TextureResource::TextureResource(int textureId):
textureId((GLuint)textureId),refCount(1){}



void TextureResource::Finalize(){

	glDeleteBuffers(1,&textureId);

}


int TextureResource::GetTextureId(){

	return textureId;
}



void TextureResource::AddReference(){

	refCount++;
}

bool TextureResource::RemoveReference(){

	refCount--;
	return refCount==0;
}

