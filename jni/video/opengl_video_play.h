#ifndef __OPENGL_VIDEO_PLAY_H
#define __OPENGL_VIDEO_PLAY_H

#include <GLES/gl.h>
#include <GLES/glext.h>

//#define TEXTURE_WIDTH 512
//#define TEXTURE_HEIGHT 256
#ifdef __cplusplus



extern "C" {
#endif
/*
 *
 * return : return -1 mean failed
 * */
extern int init_opengl_variable(int handle);
//int screen_w ,int screen_h ,int display_w ,int display_h
extern void opengl_resize();


extern void opengl_start();

extern void opengl_render();

extern GLuint s_texture;
#ifdef __cplusplus
}
#endif
int getPixelsSize();
#endif
