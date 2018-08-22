#ifndef __PICTURE_QUEUE_H
#define __PICTURE_QUEUE_H

#include <pthread.h>

#include "libavformat/avformat.h"

//typedef struct AVPictureList {
//	AVPicture pict;
//	double pts;
//	struct AVPictureList *next;
//} AVPictureList;

#define VIDEO_PACKET_NUM                        5

/*  video  frame queue*/
typedef struct Rgb565Queue {
	int front;
	int rear;

	/*  frame */
	uint8_t *rgb565_data[VIDEO_PACKET_NUM];
	double frame_pts[VIDEO_PACKET_NUM];

	pthread_mutex_t mutex;
	pthread_cond_t cond_empty; //read packet
	pthread_cond_t cond_full; //put packet
} Rgb565Queue;

/*
 *
 * return : return -1 failed
 * */
int frame_queue_init(Rgb565Queue *q, int frame_size);

int frame_queue_put(Rgb565Queue *q, AVFrame *pFrame ,int size ,double video_frame_pts  );

int frame_queue_get(Rgb565Queue *q ,/*decode_video_u */void *decode_video_var,double* video_frame_pts ,uint8_t * video_data ,int handle);

void frame_queue_destroy(Rgb565Queue *q );
#endif
