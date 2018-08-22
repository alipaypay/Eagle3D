#ifndef MOVIE_TEXTURE_H
#define MOVIE_TEXTURE_H
#include <unistd.h>
extern "C"{
#include <video/xplayer.h>

}

class MovieTexture{
private:
	PLAYER_HANDLE mediaHandle;

public:
	MovieTexture(const char* fileName);
	int GetMovieTextureID();
	virtual void Render();
	void Pause();
	void Resume();
	void ApplicationQuit();
};


#endif
