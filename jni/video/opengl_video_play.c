#include <android/log.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "opengl_video_play.h"
#include "EagleLog.h"
#include "xplayer.h"
#include "libavformat/avformat.h"
#include "decode_video.h"
#include "picture_queue.h"


//#define S_PIXELS_SIZE (2 * TEXTURE_WIDTH * TEXTURE_HEIGHT)  //rgb565 data
//#define S_PIXELS_SIZE (sizeof(s_pixels[0]) * TEXTURE_WIDTH * TEXTURE_HEIGHT)

static uint16_t *s_pixels = 0;
static pthread_cond_t s_vsync_cond;
static pthread_mutex_t s_vsync_mutex;
GLuint s_texture = 0;

static int g_stop_mark = 0;
static int g_handle = 0;
static AVFormatContext *fmt_ctx = NULL;
static decode_video_u *decode_video_var = NULL;
static double video_frame_pts;
double delay_time ;
int pixels_size=0;
int getPixelsSize(){
	if(pixels_size==0){
		pixels_size=decode_video_var->ptr_video_codec_ctx->width*decode_video_var->ptr_video_codec_ctx->height*5*sizeof(uint32_t);

	}

	return pixels_size;
}

static void check_gl_error(const char* op)
{
	GLint error;
	for (error = glGetError(); error; error = glGetError())
		LOGE("after %s() glError (0x%x)\n", op, error);
}

/* wait for the screen to redraw  */
static void wait_vsync()
{
	struct timeval now;
	struct timespec outtime;

	pthread_mutex_lock(&s_vsync_mutex);
	LOGE("wait in wait_vsync");
//	pthread_cond_wait(&s_vsync_cond, &s_vsync_mutex);
	while(1){
		gettimeofday(&now, NULL);
		outtime.tv_sec = now.tv_sec;
		outtime.tv_nsec = now.tv_usec * 1000 +  50 * 1000 * 1000;
		 pthread_cond_timedwait(&s_vsync_cond, &s_vsync_mutex,&outtime);
		 if( ((media_handle_union_t *)g_handle)->stop_mark == 1){
			 break;
		 }
	}
	LOGE("after wait in wait_vsync");
	pthread_mutex_unlock(&s_vsync_mutex);
}

static int render_pixels( uint16_t *pixels )
{

//	if(decode_video_var->finish_mark == 1){		//oh shit.
	if(((media_handle_union_t *)g_handle)->stop_mark == 1){		//oh shit.
		LOGE("g_handle->stop_mark == 1 ,and return 0");
		return -1;
	}
	video_frame_pts = 0;
	if ( -1 == frame_queue_get(&decode_video_var->rgb565_queue ,NULL,&video_frame_pts ,(uint8_t * )pixels ,decode_video_var->handle) ) {
		LOGE("==frame_queue_get failed");
		return -1;
	}

	while( ((media_handle_union_t *)decode_video_var->handle)->audio_prepared != 1 ){

		usleep(200);
		if( ((media_handle_union_t *)decode_video_var->handle)->audio_prepared == 1  ) break;
	}

	delay_time = video_frame_pts - ((media_handle_union_t *)decode_video_var->handle)->global_clock_time ;
	if(delay_time > 50){ //video too fast,and sleep ,50 millisecond
		usleep(delay_time * 1000); //in microseconds
		LOGE("video sleep ,delay_time = %f" ,delay_time);
	}
	return 0;

}

int s_w = 0;
int s_h = 0;
int display_width = 0;
int display_height = 0;
/* disable these capabilities. */
static GLuint s_disable_caps[] = {
	GL_FOG,
	GL_LIGHTING,
	GL_CULL_FACE,
	GL_ALPHA_TEST,
	GL_BLEND,
	GL_COLOR_LOGIC_OP,
	GL_DITHER,
	GL_STENCIL_TEST,
	GL_DEPTH_TEST,
	GL_COLOR_MATERIAL,
	0
};
//int screen_w ,int screen_h ,int display_w ,int display_h
void opengl_resize()
{
	//LOGE("chris_magic"  ,"w = %d ,h = %d" ,screen_w ,screen_h);
	//glDeleteTextures(1, &s_texture);


	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &s_texture);
	glBindTexture(GL_TEXTURE_2D, s_texture);

	glTexParameterf(GL_TEXTURE_2D,
			  		    GL_TEXTURE_MIN_FILTER,
			  		    GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,
			  		    GL_TEXTURE_MAG_FILTER,
			  		    GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D,
					  GL_TEXTURE_WRAP_S,
					  GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D,
					  GL_TEXTURE_WRAP_T,
					  GL_CLAMP_TO_EDGE);


	glTexImage2D(GL_TEXTURE_2D,
					 0, GL_RGB,
					 s_w,s_h,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);

}

void opengl_render(){
	memset(s_pixels, 0x00 /*0xff*/, getPixelsSize()); //the corlor of the TEXTURE ,black
	if(g_stop_mark == 1 ){
		return ;
	}
	if( render_pixels(s_pixels) == -1){    //function
		LOGE(" render failed ..... ");
		g_stop_mark = 1;
	}
	g_stop_mark = 0;
	glActiveTexture(s_texture);
	glBindTexture(GL_TEXTURE_2D, s_texture);
	glTexSubImage2D(GL_TEXTURE_2D,		/* target */
			0,			/* level */
			0,0,			/* internal format */
			s_w,		/* width */
			s_h,		/* height */
			GL_RGB,			/* border */
			GL_UNSIGNED_BYTE,/* type */
			s_pixels);		/* pixels */
	//check_gl_error("glTexSubImage2D");

//	if(s_h > s_w){ //vertical screen
//		if(display_width > s_w ){	//screen is too small
//			if(display_height < s_h){
//				glViewport(0 ,s_h -display_height ,s_w, display_height);
//				glDrawTexiOES( 0, s_h -display_height, 0, s_w, display_height);
//			}else{
//				glViewport(0 ,0 ,s_w, s_h);
//				glDrawTexiOES( 0, 0, 0, s_w, s_h);
//			}
//		}else{
//			glViewport((s_w - display_width)/2, s_h -display_height, display_width, display_height);
//			glDrawTexiOES( (s_w - display_width)/2, s_h -display_height, 0, display_width, display_height);
//		}
//
//	}else{
//		//glDrawTexiOES(0, 0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);  //the last two parameters //la shen
//		//log_chris(ANDROID_LOG_ERROR ,TAG ,"s_h < s_w ,s_h = %d ,s_w =%d"  ,s_h ,s_w);
//		glViewport(0 ,0 ,s_w, s_h);
//		glDrawTexiOES(0, 0, 0, s_w, s_h);  //the last two parameters //la shen
//	}
//
//
//
////	glDrawTexiOES(0, 0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);  //the last two parameters //la shen
//	check_gl_error("glDrawTexiOES");
	/* tell the other thread to carry on */
	pthread_cond_signal(&s_vsync_cond);  // here ,
}

//rend video
void opengl_start()
{
	LOGI("in opengl_start function ");
	/* init conditions */
	pthread_cond_init(&s_vsync_cond, NULL);
	pthread_mutex_init(&s_vsync_mutex, NULL);

	s_pixels = malloc(getPixelsSize()); //
	while (1) {
		/* wait on screen sync */

		wait_vsync();
		LOGI("==stop_mark = %d" ,((media_handle_union_t *)decode_video_var->handle)->stop_mark);
		if( ((media_handle_union_t *)decode_video_var->handle)->stop_mark == 1){
			fmt_ctx = NULL;
			decode_video_var = NULL;
//			if(s_pixels){
//				free(s_pixels);
//				s_pixels == NULL;
//			}
			LOGI("==break opengl_start ,open_start function exit");
			break;
		}
	}
}

//init ...
int  init_opengl_variable(int handle){
	media_handle_union_t * media_handle = (media_handle_union_t *) handle;
	if (media_handle == NULL) {
		LOGE("media handle is null");
		return -1;
	}

	g_stop_mark = 0;
	//init
	g_handle = handle;
	fmt_ctx = media_handle->ptr_format_ctx;
	decode_video_var = media_handle->decode_video_var;
	s_w = decode_video_var->ptr_video_codec_ctx->width;
	s_h = decode_video_var->ptr_video_codec_ctx->height;

	//-->
	LOGI("s_w = %d ,s_h = %d"  ,s_w ,s_h);
}


