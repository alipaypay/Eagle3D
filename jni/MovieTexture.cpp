#include <MovieTexture.h>
#include <video/opengl_video_play.h>



MovieTexture::MovieTexture(const char* fileName){
	PLAYER_HANDLE media_handle = init_media(fileName);
	mediaHandle=media_handle;
	sleep(0.001);
	xplayer_play(mediaHandle);
	//opengl_start();
	opengl_resize();
}

int MovieTexture::GetMovieTextureID(){

	return s_texture;

}

void MovieTexture::Render(){

	opengl_render();

}

void MovieTexture::Pause(){
	player_stop(mediaHandle);

}
void MovieTexture::Resume(){


}
void MovieTexture::ApplicationQuit(){
	player_stop(mediaHandle);


}

