#ifndef DECODE_VIDEO_H
#define DECODE_VIDEO_H


#include "libavcodec/avcodec.h"
#include "packet_queue.h"
#include "picture_queue.h"

#define VIDEO_PACKET_GET_NON_PACKET		0x002

typedef struct decode_video_union{
	/*video */
	AVCodecContext *ptr_video_codec_ctx;
	AVCodec *ptr_video_codec;
	int video_stream;

	PacketQueue video_queue;
	struct SwsContext *img_convert_ctx;

	uint8_t *decoded_video_buf;		//used to save one video frame data (in rgb565 format)
	AVFrame *decoded_frame;	//rgb565
	AVFrame *yuv_frame;

	int frame_rgb565_size;

	double video_frame_pts;
	Rgb565Queue rgb565_queue;		//use to store rgb565 data

	int finish_mark;
	AVPacket flush_pkt;
	int handle;
}decode_video_u;


/*
 *
 * return : return NULL mean init failed
 * */
decode_video_u * init_decode_video(AVFormatContext *fmt_ctx ,decode_video_u *decode_video_var);


/*
 *
 * return value : as success return 0,other is fault
 * */
int  decode_video(decode_video_u *decode_video_var ,AVFormatContext *fmt_ctx);

#endif
