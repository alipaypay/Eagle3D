#include <stdlib.h>

#include "libswscale/swscale.h"
#include "decode_video.h"
#include "packet_queue.h"
#include "xplayer.h"
#include "opengl_video_play.h"
#include "EagleLog.h"

static int malloc_rgb565_mem(decode_video_u *decode_video_var ){

#if 0
	//video
	decode_video_var->img_convert_ctx = sws_getContext(
			decode_video_var->ptr_video_codec_ctx->width,
			decode_video_var->ptr_video_codec_ctx->height,
			decode_video_var->ptr_video_codec_ctx->pix_fmt,
			decode_video_var->ptr_video_codec_ctx->width, decode_video_var->ptr_video_codec_ctx->height,
			PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);  //little endian
#endif

	//use for opengl es
	decode_video_var->img_convert_ctx = sws_getContext(
			decode_video_var->ptr_video_codec_ctx->width,
			decode_video_var->ptr_video_codec_ctx->height,
			decode_video_var->ptr_video_codec_ctx->pix_fmt,
			decode_video_var->ptr_video_codec_ctx->width, decode_video_var->ptr_video_codec_ctx->height,
			PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);  //little endian
	if(decode_video_var->img_convert_ctx == NULL){
		LOGE("sws_getContext get failed");
		return -1;
	}

	decode_video_var->yuv_frame = av_frame_alloc();
	if(decode_video_var->yuv_frame == NULL){
		LOGE("yuv_frame allocate failed");
		return -1;
	}


	decode_video_var->decoded_frame = av_frame_alloc();
	if(decode_video_var->decoded_frame == NULL){
		LOGE("pFrameRGB565 allocate failed");
		return -1;
	}

	int width = decode_video_var->ptr_video_codec_ctx->width;
	int height = decode_video_var->ptr_video_codec_ctx->height;
	int num_bytes = avpicture_get_size(/*PIX_FMT_RGB24*/PIX_FMT_RGB24, width, height);

	//log_chris(ANDROID_LOG_ERROR ,TAG ,"num_bytes_size = %d" ,num_bytes);
	//malloc memory
	decode_video_var->decoded_video_buf = (uint8_t *)av_malloc(num_bytes * sizeof(uint8_t));
	if(decode_video_var->decoded_video_buf == NULL){
		LOGE("buffer av_malloc failed ");
		return -1;
	}

	//bind
//	avpicture_fill((AVPicture *)decode_video_var->decoded_frame, decode_video_var->decoded_video_buf, PIX_FMT_RGB565LE, width, height);
	avpicture_fill((AVPicture *)decode_video_var->decoded_frame, decode_video_var->decoded_video_buf, PIX_FMT_RGB24,
			width, height);

	return 0;
}

decode_video_u * init_decode_video(AVFormatContext *fmt_ctx ,decode_video_u *decode_video_var){

	/* start to find audio stream && video stream */
	int i;
	decode_video_var->video_stream = -1;
	for (i = 0; i < fmt_ctx->nb_streams; i++) {
		if (fmt_ctx->streams[i]->codec->codec_type
				== AVMEDIA_TYPE_VIDEO ) {			//only find the first video stream
			decode_video_var->video_stream = i;
			break;
		}
	}

	if (decode_video_var->video_stream < 0) {
		LOGE("can not find video stream in file");
		return NULL;
	}

	/* video	*/
	decode_video_var->ptr_video_codec_ctx = fmt_ctx->streams[decode_video_var->video_stream]->codec;
	if ((decode_video_var->ptr_video_codec = avcodec_find_decoder(
			decode_video_var->ptr_video_codec_ctx->codec_id)) == NULL) {
		LOGE("find video decoder failed");
		return NULL;
	}

	LOGI("before avcodec_open2 ,decode_video_var->ptr_video_codec_ctx->codec_id = %d" ,decode_video_var->ptr_video_codec_ctx->codec_id);
	// open video decoder
	if (avcodec_open2(decode_video_var->ptr_video_codec_ctx, decode_video_var->ptr_video_codec ,NULL) < 0) {
		LOGE("open video decoder failed");
		return NULL;
	}

	LOGI("before packet_queue_init ,sr_width = %d" ,decode_video_var->ptr_video_codec_ctx->width);
	packet_queue_init(&decode_video_var->video_queue);
	decode_video_var->video_queue.packet_max_num = VIDEO_PACKET_MAX_NUM;
	LOGI("after packet_queue_init , and before malloc rgb565 mem");

	int ret =malloc_rgb565_mem( decode_video_var );
	if(ret < 0){
		LOGE("malloc rgb memory failed");
		return NULL;
	}
	LOGI("after malloc rgb565 mem");

	//	decode_video_var->frame_rgb565_size = decode_video_var->ptr_video_codec_ctx->width
//									* decode_video_var->ptr_video_codec_ctx->height * 2;
	decode_video_var->frame_rgb565_size = decode_video_var->ptr_video_codec_ctx->height* decode_video_var->ptr_video_codec_ctx->width * 5 * sizeof(uint32_t);
	LOGI("before frame_queue_init ,frame_rgb565_size = %d" ,decode_video_var->frame_rgb565_size);

	//init frame_queue
	if( frame_queue_init(&decode_video_var->rgb565_queue, /*decode_video_var->frame_rgb565_size*/decode_video_var->ptr_video_codec_ctx->height* decode_video_var->ptr_video_codec_ctx->width * 5 * sizeof(uint32_t)) < 0){
		LOGE("frame_queue_init failed");
		return NULL;
	}
	LOGI("after frame_queue_init");
	return decode_video_var;
}

//decode_video // uint8_t * video_mem_addr
int  decode_video(decode_video_u *decode_video_var ,AVFormatContext *fmt_ctx){
	static AVPacket pkt1;
	static AVPacket *pkt = &pkt1;
	//log_chris(ANDROID_LOG_ERROR ,TAG ,"in decode_video ....");
	for (;;) {
		if (packet_queue_get(&decode_video_var->video_queue, pkt, decode_video_var->finish_mark ,decode_video_var->handle) < 0) {
			LOGE("video packet queue get fail ,file_over = %d" ,decode_video_var->finish_mark);
			return VIDEO_PACKET_GET_NON_PACKET;

		}

		LOGI("before decode video pakcet.num = %d" ,decode_video_var->video_queue.nb_packets );
		int got_picture = 0;
		avcodec_decode_video2(decode_video_var->ptr_video_codec_ctx ,decode_video_var->yuv_frame, &got_picture, pkt);


		if (got_picture) {
			//			int64_t pts1 = media_handle->yuv_frame->best_effort_timestamp;
			int64_t pts1 = decode_video_var->yuv_frame->pkt_pts;
			decode_video_var->video_frame_pts =
					(double) pts1
							* av_q2d(
									fmt_ctx->streams[decode_video_var->video_stream]->time_base)
							* 1000; //in millisecond
			//log_chris(ANDROID_LOG_INFO,TAG, "video pts = %f" ,decode_video_var->video_frame_pts);

			( (media_handle_union_t *)decode_video_var->handle )->video_prepared = 1;
			int audio_prepared = ( (media_handle_union_t *)decode_video_var->handle )->audio_prepared;
			if( (audio_prepared == 1)  && ( ((media_handle_union_t *)decode_video_var->handle)->global_clock_time - decode_video_var->video_frame_pts
					>= 200) ){ //if video is slower than audio more than 200 millisecond ,then drop video frame
					//drop frame
					//log_chris(ANDROID_LOG_INFO,"chris_magic", "drop frame ..");
					continue;
			}
//			((media_handle_union_t *)decode_audio_var->handle)->global_clock_time
#if 0
//			sws_scale(decode_video_var->img_convert_ctx,
//					(const uint8_t* const *) decode_video_var->yuv_frame->data,
//					decode_video_var->yuv_frame->linesize, 0,
//					decode_video_var->ptr_video_codec_ctx->height,
//					decode_video_var->decoded_frame->data,
//					decode_video_var->decoded_frame->linesize);
#endif
//			int sws_scale(struct SwsContext *c, const uint8_t *const srcSlice[],
//			              const int srcStride[], int srcSliceY, int srcSliceH,
//			              uint8_t *const dst[], const int dstStride[]);
			//log_chris(ANDROID_LOG_INFO,"chris_magic", "before sws_scale ,height = %d ,heiht = %d" ,decode_video_var->ptr_video_codec_ctx->height ,decode_video_var->yuv_frame->height);
//			if(decode_video_var->img_convert_ctx){
//				log_chris(ANDROID_LOG_INFO,"chris_magic", "img_convert is not null");
//			}
//			if(decode_video_var->decoded_frame->data){
//				log_chris(ANDROID_LOG_INFO,"chris_magic", "decoded_frame is not null,linesize= %d"  ,decode_video_var->decoded_frame->linesize);
//			}

			sws_scale(decode_video_var->img_convert_ctx,
								(const uint8_t* const *) decode_video_var->yuv_frame->data,
								decode_video_var->yuv_frame->linesize, 0,
								decode_video_var->ptr_video_codec_ctx->height,
								decode_video_var->decoded_frame->data,
								decode_video_var->decoded_frame->linesize);

			//log_chris(ANDROID_LOG_INFO,"chris_magic", "after sws_scale ,height = %d" ,decode_video_var->ptr_video_codec_ctx->height );
			//log_chris(ANDROID_LOG_INFO,"chris_magic", "frame_rgb565_size = %d" ,decode_video_var->frame_rgb565_size);
			//push rgb565_data into queue
			frame_queue_put(&decode_video_var->rgb565_queue,
					decode_video_var->decoded_frame,
					decode_video_var->frame_rgb565_size,
					decode_video_var->video_frame_pts);
			av_free_packet(pkt);
			return 0;

		} else { // no data
			LOGI("in cache");

		}

		av_free_packet(pkt);
	} //for(;;)

}
