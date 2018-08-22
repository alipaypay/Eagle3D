#ifndef DECODE_AUDIO_H
#define DECODE_AUDIO_H

#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "packet_queue.h"
typedef struct decode_audio_union{

	/* audio */
	PacketQueue audio_queue;

	int audio_stream;				//audio stream index

	AVCodecContext *ptr_audio_codec_ctx;
	AVCodec *ptr_audio_codec;


	AVFrame *audio_decoded_frame;	//the decoded audio frame ,pcm data
	int audio_pkt_size;				//use for the audio_decode function

	double audio_frame_pts;			//audio frame pts

	int bytes_per_sec;				//use to store the size of one second audio data(in pcm format)
	int audio_size;

	int finish_mark;
	AVPacket flush_pkt;

	int handle;
}decode_audio_u;

/*
 *
 *return value: return NULL ,failed
 * */
decode_audio_u * init_decode_audio(AVFormatContext *fmt_ctx ,decode_audio_u * decode_audio_var);

/*
 * return the decoded_audio_frame data len
 * */
int  decode_audio(decode_audio_u *decode_audio_var , uint8_t * audio_mem_addr ,AVFormatContext *fmt_ctx);

#endif
