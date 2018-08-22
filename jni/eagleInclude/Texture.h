#ifndef TEXTURE_H
#define TEXTURE_H

#define PNG_LIBPNG_VER_STRING "1.6.13"

#include <GLES2/gl2.h>
#include <GLES/gl.h>
#include <EGL/egl.h>
#include <stdio.h>
#ifdef _Android_
	#include "Java2C.h"
#endif
#include <vector>
#include <string>
#include "Tools.h"
#include "TextureResource.h"

#include <Java2C.h>
#include "src/SDL_internal.h"
#include <android/asset_manager.h>
#include <CoreActivity.h>
extern "C"{
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
}
#include <map>
#include <MovieTexture.h>
using namespace std;
class Texture{

private:
	map<string,TextureResource*> textureResource;
	map<string,TextureResource*>::iterator textureResource_iter;
	TextureResource* resource;

	 MovieTexture* movieTexture;
	// SDL_MovieTexture *sdl_movieTex;
	string fileNameStr;

	 //##########################################
	 //Load texture in assets folder
	 int LoadTextureInAssets(const char* fileName);
	 int ReadTextureInAssets(const char* fileName);

	 SDL_RWops * AAsset_RWFromAsset(const char *filename);
	 static SDLCALL size_t aa_rw_read(struct SDL_RWops * ops, void *ptr, size_t size, size_t maxnum);
	 static SDLCALL Sint64 aa_rw_seek(struct SDL_RWops * ops, Sint64 offset, int whence);
	 static SDLCALL int aa_rw_close(struct SDL_RWops * ops);
	//##########################################
	 //Load Texture in external card
	 int LoadTexture(const char* fileName);

	 int ReadTexture(const char* filename);

public:

	void Render();
	Texture(const char* fileName,bool isLoadInner);
	void AddTexture(const char* fileName,bool isLoadInner);
	Texture();
	~Texture();
	void AddTexture(int tId);
	int GetTextureId();
	void Bind();
	void Finalize();
	void Pause();
	void Resume();
	void ApplicationQuit();



};

#endif
