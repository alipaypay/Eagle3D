#include "Texture.h"
#include <sstream>
Texture::Texture(){
	movieTexture=NULL;
	//sdl_movieTex=NULL;
	//this->id=LoadTextureInAssets("assets/default.png");

}

Texture::Texture(const char* fileName,bool isLoadInner){
	AddTexture(fileName,isLoadInner);
}



Texture::~Texture(){
	//Finalize();
//delete resource;
	//resource=0;
}

int Texture::GetTextureId(){

	return this->resource->GetTextureId();

}

void Texture::AddTexture(const char* fileName,bool isLoadInner){
			movieTexture=NULL;
			string str(fileName);
			fileNameStr=str;
			textureResource_iter=textureResource.find(fileNameStr);
			if(textureResource_iter!=textureResource.end()){

				resource=textureResource[fileNameStr];
				resource->AddReference();
			}
			else{
				int texId=-1;
				if(isLoadInner){
					texId=LoadTextureInAssets(fileName);
				}else{
					texId=LoadTexture(fileName);
				}
				resource=new TextureResource(texId);
				textureResource[fileNameStr]=resource;

			}

}

void Texture::AddTexture(int tId){
	 	 	    stringstream ss;
	 	 	    string str;
	 	 	    ss<<tId;
	 	 	    ss>>str;
				fileNameStr=str;
				textureResource_iter=textureResource.find(fileNameStr);
				if(textureResource_iter!=textureResource.end()){

					resource=textureResource[fileNameStr];
					resource->AddReference();
				}
				else{

					resource=new TextureResource(tId);
					textureResource[fileNameStr]=resource;

			}
}

void Texture::Bind(){
	 glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,resource->GetTextureId());

}



int Texture::LoadTextureInAssets(const char* fileName){
	 vector<string> spliteArr;
	 Tools::SplitString(fileName,".",spliteArr);
	 string ext=spliteArr[spliteArr.size()-1];


	 if(strcmp(ext.c_str(),"png")==0 || strcmp(ext.c_str(),"bmp")==0 || strcmp(ext.c_str(),"jpg")==0 || strcmp(ext.c_str(),"tga")==0){
		 return ReadTextureInAssets(fileName);

	 }else if(strcmp(ext.c_str(),"avi") || strcmp(ext.c_str(),"mp4") || strcmp(ext.c_str(),"flv") || strcmp(ext.c_str(),"3gp")){
		 //sdl_movieTex=new SDL_MovieTexture(fileName);
		 movieTexture=new MovieTexture(fileName);
		 return movieTexture->GetMovieTextureID();
	 }else{
		 LOGE("Is not a standard image format");
	 }

	return -1;
}

int Texture::ReadTextureInAssets(const char* fileName){
	 	 	LOGI("Read Image from external sdcard start1");
			SDL_Surface *image;
		    SDL_Rect area;

		    SDL_RWops *file = AAsset_RWFromAsset( fileName);;
		    SDL_Surface *pSurface = IMG_Load_RW(file, 1);;
		    LOGI("Read Image from external sdcard start2");
		    image = SDL_CreateRGBSurface(
		    SDL_SWSURFACE,
		    pSurface->w, pSurface->h,
		    32,
		    #if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
		    0x000000FF,
		    0x0000FF00,
		    0x00FF0000,
		    0xFF000000
		    #else
		    0xFF000000,
		    0x00FF0000,
		    0x0000FF00,
		    0x000000FF
		    #endif
		    );
		    LOGI("Read Image from external sdcard start3");
		    if ( image == NULL ) {
		    	LOGE("Error:SDL Create Surface Error!");
		    	return -1;
		     }
		    /* Copy the surface into the GL texture image */
		     area.x = 0;
		     area.y = 0;
		     area.w = pSurface->w;
		     area.h = pSurface->h;
		     SDL_BlitSurface(pSurface, &area, image, &area);
		    /* Restore the alpha blending attributes */
		     SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);
		     LOGI("Read Image from external sdcard start4");
		     /* Create an OpenGL texture for the image */
		     GLuint texture;
		     glGenTextures(1, &texture);
		     glBindTexture(GL_TEXTURE_2D, texture);
		     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		     glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		     glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	         glTexImage2D(GL_TEXTURE_2D,
		    			    0,
		    			    GL_RGBA,
		    			    image->w, image->h,
		    			    0,
		    			    GL_RGBA,
		    			    GL_UNSIGNED_BYTE,
		    			    image->pixels);
		      SDL_FreeSurface(image);
		      SDL_FreeSurface(pSurface);
		      return texture;
}

int Texture::ReadTexture(const char* filename){

// LOGI("file name:%s",argv[1]);
	    SDL_Surface *image;
	    SDL_Rect area;

	    SDL_Surface *pSurface = IMG_Load(filename);
	    LOGI("Read Image from external sdcard start2");
	    image = SDL_CreateRGBSurface(
	    SDL_SWSURFACE,
	    pSurface->w, pSurface->h,
	    32,
	    #if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
	    0x000000FF,
	    0x0000FF00,
	    0x00FF0000,
	    0xFF000000
	    #else
	    0xFF000000,
	    0x00FF0000,
	    0x0000FF00,
	    0x000000FF
	    #endif
	    );
	    LOGI("Read Image from external sdcard start3");
	    if ( image == NULL ) {
	    	LOGE("Error:SDL Create Surface Error!");
	    	return -1;
	     }
	    /* Copy the surface into the GL texture image */
	     area.x = 0;
	     area.y = 0;
	     area.w = pSurface->w;
	     area.h = pSurface->h;
	     SDL_BlitSurface(pSurface, &area, image, &area);
	    /* Restore the alpha blending attributes */
	     SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);
	     LOGI("Read Image from external sdcard start4");
	     /* Create an OpenGL texture for the image */
	     GLuint texture;
	     glGenTextures(1, &texture);
	     glBindTexture(GL_TEXTURE_2D, texture);
	     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	     glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	     glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
         glTexImage2D(GL_TEXTURE_2D,
	    			    0,
	    			    GL_RGBA,
	    			    image->w, image->h,
	    			    0,
	    			    GL_RGBA,
	    			    GL_UNSIGNED_BYTE,
	    			    image->pixels);
	      SDL_FreeSurface(image);
	      SDL_FreeSurface(pSurface);
	      return texture;

}

int Texture::LoadTexture(const char* fileName){
	 	 vector<string> spliteArr;
		 Tools::SplitString(fileName,".",spliteArr);
		 string ext=spliteArr[spliteArr.size()-1];


		 if(strcmp(ext.c_str(),"png")==0 || strcmp(ext.c_str(),"bmp")==0 || strcmp(ext.c_str(),"jpg")==0 || strcmp(ext.c_str(),"tga")==0){
			 return ReadTexture(fileName);
		 }else if(strcmp(ext.c_str(),"avi") || strcmp(ext.c_str(),"mp4") || strcmp(ext.c_str(),"flv") || strcmp(ext.c_str(),"3gp")){
			 //movieTexture=new MovieTexture(fileName);
			 movieTexture=new MovieTexture(fileName);
			 return movieTexture->GetMovieTextureID();
		 }else{
			 LOGE("Is not a standard image format");
		 }

		 return -1;
}

void Texture::Finalize(){
	//LOGI("Texture FINALIZE");
	movieTexture=NULL;
	delete movieTexture;
	if(resource->RemoveReference()){
		textureResource_iter=textureResource.find(fileNameStr);
		if(textureResource_iter!=textureResource.end() && fileNameStr.length()!=0){

			textureResource.erase(textureResource_iter);
		}

	}

}

SDLCALL Sint64 Texture::aa_rw_seek(struct SDL_RWops * ops, Sint64 offset, int whence){

	return AAsset_seek((AAsset*)ops->hidden.unknown.data1, offset, whence);
}

SDLCALL size_t Texture::aa_rw_read(struct SDL_RWops * ops, void *ptr, size_t size, size_t maxnum){

	return AAsset_read((AAsset*)ops->hidden.unknown.data1, ptr, maxnum * size) / size;

}
SDLCALL int Texture::aa_rw_close(struct SDL_RWops * ops){
		AAsset_close((AAsset*)ops->hidden.unknown.data1);
		SDL_FreeRW(ops);
		return 0;
}

SDL_RWops * Texture::AAsset_RWFromAsset(const char *filename){
	 AAsset *asset= AAssetManager_open(CoreActivity::GetActivity()->assetManager, filename, AASSET_MODE_RANDOM);
	 if(!asset){
		 return NULL;
	 }
	 SDL_RWops *ops=SDL_AllocRW();
	 if(!ops){
		 AAsset_close(asset);
		 return NULL;
	 }
	 ops->hidden.unknown.data1=asset;
	 ops->read=aa_rw_read;
	 ops->write=NULL;
	 ops->seek=aa_rw_seek;
	 ops->close=aa_rw_close;
	 return ops;
}

void Texture::Render(){
	if(movieTexture!=NULL){
		movieTexture->Render();
	}


}

void Texture::Pause(){
	if(movieTexture!=NULL){
			movieTexture->Pause();
		}

}
void Texture::Resume(){
	if(movieTexture!=NULL){
			movieTexture->Resume();
		}
}
void Texture::ApplicationQuit(){
	if(movieTexture!=NULL){
			movieTexture->ApplicationQuit();
		}

}


